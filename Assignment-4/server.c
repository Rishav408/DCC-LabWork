#include <stdio.h>
#include <winsock2.h>

#define PORT 8080
#define MAX_EVENTS 100

typedef struct {
    int logical_clock;
    int event_count;
} ProcessState;

ProcessState server_state;

void init_server() {
    server_state.logical_clock = 0;
    server_state.event_count = 0;
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

    // Initialize server state
    init_server();

    // Receive message from client
    int recv_len = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    if (recv_len > 0) {
        buffer[recv_len] = '\0';
        printf("Received message from client: %s\n", buffer);
        server_state.event_count++;

        // Lamport Logical Clock: increment on event
        server_state.logical_clock++;
        printf("After event %d, logical clock = %d\n", server_state.event_count, server_state.logical_clock);

        // Format response with logical clock
        sprintf(response, "Message processed. Logical clock: %d", server_state.logical_clock);
    } else {
        printf(" recv failed or connection closed\n");
    }

    // Send response to client
    send(client_fd, response, strlen(response), 0);
    printf("Response sent to client.\n");

    // Close connections
    closesocket(client_fd);
    closesocket(server_fd);
    WSACleanup();
    printf("Server closed.\n");

    return 0;
}