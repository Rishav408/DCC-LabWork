#include <stdio.h>
#include <winsock2.h>

#define PORT 8080
#define MAX_PROCESSES 10

int processes[MAX_PROCESSES];
int n;
int coordinator;

void election(int initiator) {
    int i;
    printf("\nProcess %d is initiating election...\n", initiator);

    for (i = initiator + 1; i < n; i++) {
        if (processes[i] == 1) {
            printf("Process %d sends election message to Process %d\n", initiator, i);
            election(i);
        }
    }
    coordinator = initiator;
}

void displayCoordinator() {
    printf("\nCurrent Coordinator is Process %d\n", coordinator);
}

int main() {
    WSADATA wsaData;
    SOCKET server_fd, client_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char response[1024] = {0};

    // Initialize Winsock
    printf("\nInitializing Winsock...\n");
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Winsock initialization failed. Error Code: %d\n", WSAGetLastError());
        return 1;
    }
    printf("Winsock initialized successfully.\n");

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Socket creation failed. Error Code: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    printf("Socket created successfully.\n");

    // Set socket options
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));

    // Bind socket
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == SOCKET_ERROR) {
        printf("Bind failed. Error Code: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }
    printf("Binding successful. Server listening on port %d...\n", PORT);

    // Listen
    if (listen(server_fd, 3) == SOCKET_ERROR) {
        printf("Listen failed. Error Code: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }
    printf("Server is listening for connections...\n");

    // Accept client connection
    if ((client_fd = accept(server_fd, (struct sockaddr *)&address, &addrlen)) == INVALID_SOCKET) {
        printf("Accept failed. Error Code: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }
    printf("Client connected from IP: %s, Port: %d\n",
           inet_ntoa(address.sin_addr), ntohs(address.sin_port));

    // Initialize Bully Algorithm state
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter status of each process (1 = Active, 0 = Failed):\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i);
        scanf("%d", &processes[i]);
    }

    printf("Enter the process which detects failure: ");
    int failed;
    scanf("%d", &failed);

    // Run election algorithm
    election(failed);
    displayCoordinator();

    // Send response to client
    sprintf(response, "Coordinator elected: Process %d", coordinator);
    send(client_fd, response, strlen(response), 0);
    printf("Response sent to client.\n");

    // Close connections
    closesocket(client_fd);
    closesocket(server_fd);
    WSACleanup();
    printf("Server closed.\n");

    return 0;
}