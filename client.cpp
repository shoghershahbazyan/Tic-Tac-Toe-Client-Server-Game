#include <iostream>
#include <string>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[1024];

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("Error in socket");
        exit(1);
    }
    std::cout << "Client socket created.\n";

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Error in connection");
        exit(1);
    }
    std::cout << "Connected to server.\n";
    std::cout << "First\n";
    
    while (true) {
        std::string message;
        std::cout << "Client: ";
        getline(std::cin, message);
        send(clientSocket, message.c_str(), message.size(), 0);
        if (message == "exit") {
            std::cout << "Client disconnected.\n";
            break;
        }
        recv(clientSocket, buffer, 1024, 0);
        std::cout << "Server: " << buffer << std::endl;
        if (std::string(buffer) == "exit") {
            std::cout << "Server disconnected.\n";
            break;
        }
    }

    close(clientSocket);

    return 0;
}

