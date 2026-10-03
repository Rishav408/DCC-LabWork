#include <stdio.h>
#include <winsock2.h>

#define PORT 8080

int main() {
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in server_addr;
    char buffer[1024] = {0};
    char message[] = "Hello from Client";

    // Initialize Winsock
    printf("\nInitializing Winsock...\n");
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Winsock initialization failed. Error Code: %d\n", WSAGetLastError());
        return 1;
    }
    printf("Winsock initialized successfully.\n");

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Socket creation failed. Error Code: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    printf("Socket created successfully.\n");

    // Set up server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Connection failed. Error Code: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    printf("Connected to server at 127.0.0.1:%d\n", PORT);

    // Send message to server
    printf("Sending message: %s\n", message);
    if (send(sock, message, strlen(message), 0) == SOCKET_ERROR) {
        printf("Send failed. Error Code: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    printf("Message sent.\n");

    // Receive response from server
    int recv_len = recv(sock, buffer, sizeof(buffer) - 1, 0);
    if (recv_len > 0) {
        buffer[recv_len] = '\0';
        printf("Received from server: %s\n", buffer);
    } else {
        printf(" recv failed or connection closed\n");
    }

    // Close socket
    closesocket(sock);
    WSACleanup();
    printf("Client closed.\n");

    return 0;
}