#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PORT 8080
#define SERVER_IP "127.0.0.1"

int main()
{
    WSADATA wsa;
    SOCKET clientSocket;
    struct sockaddr_in serverAddr;
    int result;

    char message[] = "Hello from Client";
    char buffer[1024] = {0};

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed with error: %d\n", WSAGetLastError());
        return 1;
    }

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        printf("Socket creation failed with error: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Set up server address structure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    if (serverAddr.sin_addr.s_addr == INADDR_NONE) {
        printf("Invalid IP address: %s\n", SERVER_IP);
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    // Connect to server
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Connection failed with error: %d\n", WSAGetLastError());
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    printf("Connected to server at %s:%d\n", SERVER_IP, PORT);

    // Send message
    result = send(clientSocket, message, (int)strlen(message), 0);
    if (result == SOCKET_ERROR) {
        printf("Send failed with error: %d\n", WSAGetLastError());
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    printf("Client: %s\n", message);

    // Receive reply
    result = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (result == SOCKET_ERROR) {
        printf("Recv failed with error: %d\n", WSAGetLastError());
    } else if (result == 0) {
        printf("Connection closed by server\n");
    } else {
        buffer[result] = '\0';
        printf("Server: %s\n", buffer);
    }

    // Cleanup
    closesocket(clientSocket);
    WSACleanup();

    printf("Client closed.\n");
    return 0;
}