#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PORT 8080
#define LISTEN_BACKLOG 3

int main()
{
    WSADATA wsa;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int clientAddrSize = sizeof(clientAddr);
    int result;

    char buffer[1024] = {0};
    char message[] = "Hello from Server";
    char clientIP[INET_ADDRSTRLEN];

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed with error: %d\n", WSAGetLastError());
        return 1;
    }

    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        printf("Socket creation failed with error: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Set up server address structure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Bind socket to port
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Bind failed with error: %d\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, LISTEN_BACKLOG) == SOCKET_ERROR) {
        printf("Listen failed with error: %d\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    printf("Server is listening on port %d...\n", PORT);

    // Accept client connection
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);
    if (clientSocket == INVALID_SOCKET) {
        printf("Accept failed with error: %d\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Get client IP address
    strncpy(clientIP, inet_ntoa(clientAddr.sin_addr), INET_ADDRSTRLEN - 1);
    clientIP[INET_ADDRSTRLEN - 1] = '\0';
    printf("Client connected from IP: %s, Port: %d\n", clientIP, ntohs(clientAddr.sin_port));

    // Receive message from client
    result = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (result == SOCKET_ERROR) {
        printf("Recv failed with error: %d\n", WSAGetLastError());
    } else if (result == 0) {
        printf("Client closed the connection\n");
    } else {
        buffer[result] = '\0';
        printf("Client: %s\n", buffer);
    }

    // Send reply to client
    result = send(clientSocket, message, (int)strlen(message), 0);
    if (result == SOCKET_ERROR) {
        printf("Send failed with error: %d\n", WSAGetLastError());
    } else {
        printf("Server: %s\n", message);
    }

    // Cleanup
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    printf("Server closed.\n");
    return 0;
}