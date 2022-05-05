#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>

# include "Socket.hpp"

class Socket;

class Server
{
    private:
        //Socket      socket;
        int     _socketFD;
    
    public:
        Server( void );
        Server( const std::string &configFilePath );
        ~Server( void );

};

#endif