#include <iostream>
#include <string>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
int main() {
    int serverSocket, newSocket;
    struct sockaddr_in serverAddr, newAddr;
    socklen_t addrSize;
    char buffer[1024];

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("Error in socket");
        exit(1);
    }
    std::cout << "Server socket created.\n";
    //int flags = fcntl(serverSocket, F_GETFL, 0);
    //fcntl(serverSocket, F_SETFL, flags | O_NONBLOCK);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Error in binding");
        exit(1);
    }
    std::cout << "Binding success.\n";

    if (listen(serverSocket, 10) == 0) {
        std::cout << "Listening...\n";
    } else {
        std::cout << "Error in listening.\n";
    }

    addrSize = sizeof(newAddr);
    newSocket = accept(serverSocket, (struct sockaddr*)&newAddr, &addrSize);
    
    while (true) {
        recv(newSocket, buffer, 1024, 0);
        if (std::string(buffer) == "exit") {
            std::cout << "Client disconnected.\n";
            break;
        }
        std::cout << "Client: " << buffer << std::endl;
        std::string message;
        std::cout << "Server: ";
        getline(std::cin, message);
        send(newSocket, message.c_str(), message.size(), 0);
        if (message == "exit") {
            std::cout << "Server disconnected.\n";
            break;
        }
    }

    close(newSocket);
    close(serverSocket);

    return 0;
}
