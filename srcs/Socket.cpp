#include "../incl/Socket.hpp"

Socket::Socket( void )
{
    _ip = htonl(INADDR_ANY);
    _port = htons(12345);

    struct sockaddr_in  sockAddr;

    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.s_addr = _ip;
    sockAddr.sin_port = _port;
    
}

Socket::~Socket( void ) {}