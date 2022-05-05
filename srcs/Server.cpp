#include "../incl/Server.hpp"

Server::Server( void )
{
    sockaddr_in     sockAddr;

    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = htons(12345);
    sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    _socketFD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    bind(_socketFD, (struct sockaddr *) &sockAddr, sizeof(sockAddr));
    listen(_socketFD, SOMAXCONN);

    while (true)
    {
        int clientSocket = accept(_socketFD, 0, 0);
        int buff[5] = {0, 0, 0, 0, 0};
        recv(clientSocket, buff, 4, MSG_NOSIGNAL);
        shutdown(clientSocket, SHUT_RDWR);
        close(clientSocket);
        //std::cout << buff[0] << std::endl;
        printf("%s\n", buff);
    }
}
/*
Server::Server( const std::string &configFilePath )
{
    sockaddr_in     sockAddr;

    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = htons(12345);
    sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    _socketFD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    bind(_socketFD, (struct sockaddr *) &sockAddr, sizeof(sockAddr));
    listen(_socketFD, SOMAXCONN);

}
*/
Server::~Server( void ) {}