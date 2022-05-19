#ifndef SOCKET_HPP
# define SOCKET_HPP

# include <sys/socket.h>
# include <netinet/in.h>
# include <sys/types.h>
# include <sys/epoll.h>
# include <unistd.h>
# include <fcntl.h>

# define MAX_EVENTS 32
class Socket
{
    public:
        int         _socketFD;
        in_addr_t   _ip;
        uint16_t    _port;

    public:
        Socket( void );
        ~Socket( void );
};

#endif