#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 10

SOCKET clients[MAX_CLIENTS];
int client_count = 0;
CRITICAL_SECTION lock;

void remove_client(int index) {
    closesocket(clients[index]);
    clients[index] = clients[client_count - 1]; // Last client ko replace karo
    client_count--;
}

int main() {
    WSADATA wsa;
    SOCKET server_socket, new_socket;
    struct sockaddr_in server_addr, client_addr;
    int addr_size = sizeof(client_addr);

    WSAStartup(MAKEWORD(2, 2), &wsa);
    InitializeCriticalSection(&lock);

    // Socket create
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        printf("Socket creation failed!\n");
        return 1;
    }

    // Bind server
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Bind failed!\n");
        return 1;
    }

    // Listen for connections
    listen(server_socket, MAX_CLIENTS);
    printf("Server is listening on port %d...\n", PORT);

    fd_set read_fds;
    while (1) {
        FD_ZERO(&read_fds);
        FD_SET(server_socket, &read_fds);
        int max_fd = server_socket;

        EnterCriticalSection(&lock);
        for (int i = 0; i < client_count; i++) {
            FD_SET(clients[i], &read_fds);
            if (clients[i] > max_fd) {
                max_fd = clients[i];
            }
        }
        LeaveCriticalSection(&lock);

        int activity = select(max_fd + 1, &read_fds, NULL, NULL, NULL);
        if (activity < 0) {
            printf("Select error!\n");
            continue;
        }

        // New client connection
        if (FD_ISSET(server_socket, &read_fds)) {
            new_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_size);
            if (new_socket == INVALID_SOCKET) {
                printf("Client accept failed!\n");
                continue;
            }

            printf("New client connected: %s\n", inet_ntoa(client_addr.sin_addr));

            EnterCriticalSection(&lock);
            if (client_count < MAX_CLIENTS) {
                clients[client_count++] = new_socket;
            } else {
                printf("Max clients reached, rejecting connection.\n");
                closesocket(new_socket);
            }
            LeaveCriticalSection(&lock);
        }

        // Message handling
        EnterCriticalSection(&lock);
        for (int i = 0; i < client_count; i++) {
            if (FD_ISSET(clients[i], &read_fds)) {
                char buffer[BUFFER_SIZE];
                int bytes_received = recv(clients[i], buffer, BUFFER_SIZE, 0);
                if (bytes_received > 0) {
                    buffer[bytes_received] = '\0';
                    printf("Client: %s\n", buffer);

                    // Broadcast message
                    for (int j = 0; j < client_count; j++) {
                        if (clients[j] != clients[i]) {
                            send(clients[j], buffer, bytes_received, 0);
                        }
                    }
                } else {
                    printf("Client disconnected.\n");
                    remove_client(i);
                    i--;  
                }
            }
        }
        LeaveCriticalSection(&lock);
    }

    DeleteCriticalSection(&lock);
    closesocket(server_socket);
    WSACleanup();
    return 0;
}
