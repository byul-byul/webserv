#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <set>

# include "Socket.hpp"

class Socket;

class Server
{
    private:
        std::set<int>     _clientSocketList;
        Socket            _masterSocket;
    
    public:
        Server( void );
        Server( const std::string &configFilePath );
        ~Server( void );

};

#endif