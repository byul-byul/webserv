#ifndef SOCKET_HPP
# define SOCKET_HPP

# include <sys/socket.h>
# include <netinet/in.h>
# include <sys/types.h>
# include <unistd.h>

class Socket
{
    private:
        int     _socketFD;
    
    public:
        Socket( void );
        ~Socket( void );
};

#endif