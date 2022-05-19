#include "../incl/Server.hpp"
# include <algorithm>

int setNonBlock(int fd)
{
    int     flags;

#if defined(O_NONBLOCK)
    if (-1 == (flags = fcntl(fd, F_GETFL, 0)))
        flags = 0;
    return (fcntl(fd, F_SETFL, flags | O_NONBLOCK));
#else
    flags = 1;
    return (ioctl(fd, FIOBIO, &flags));
#endif
}

Server::Server( void )
{
    _masterSocket._socketFD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    struct sockaddr_in     sockAddr;

    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = htons(12345);
    sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(_masterSocket._socketFD, (struct sockaddr *) &sockAddr, sizeof(sockAddr));
    setNonBlock(_masterSocket._socketFD);
    listen(_masterSocket._socketFD, SOMAXCONN);

    int     ePoll = epoll_create1(0);

    struct  epoll_event     epEvent;
    epEvent.data.fd = _masterSocket._socketFD;
    epEvent.events = EPOLLIN;
    epoll_ctl(ePoll, EPOLL_CTL_ADD, _masterSocket._socketFD, &epEvent);

    while (true)
    {
        struct epoll_event      eventss[MAX_EVENTS];
        int                     count = epoll_wait(ePoll, eventss, MAX_EVENTS, -1);
        
        for (unsigned int i = 0; i < count; i++)
        {
            if (eventss[i].data.fd == _masterSocket._socketFD)
            {
                int     clientSocket = accept(_masterSocket._socketFD, 0, 0);
                setNonBlock(clientSocket);
                epoll_ctl(ePoll, EPOLL_CTL_ADD, clientSocket, &epEvent);
            }
            else
            {
                static char     buff[1024];
                int             recvRes = recv(eventss[i].data.fd, buff, 1024, MSG_NOSIGNAL);

                if ((recvRes == 0) && (errno != EAGAIN))
                {
                    shutdown(eventss[i].data.fd, SHUT_RDWR);
                    close(eventss[i].data.fd);
                }
                else if (recvRes > 0)
                {
                    send(eventss[i].data.fd, buff, recvRes, MSG_NOSIGNAL);
                }

            }
        }
        
        
        /*
        fd_set      sett;
        FD_ZERO(&sett);
        FD_SET(_masterSocket._socketFD, &sett);

        for (auto Iter = _clientSocketList.begin(); Iter != _clientSocketList.end(); Iter++)
        {
            FD_SET(*Iter, &sett);
        }

        int maxx = std::max(_masterSocket._socketFD, *std::max_element(_clientSocketList.begin(), _clientSocketList.end()));
        
        select(maxx + 1, &sett, NULL, NULL, NULL);
        
        for (auto Iter = _clientSocketList.begin(); Iter != _clientSocketList.end(); Iter++)
        {
            if (FD_ISSET(*Iter, &sett))
            {
                static char     buff[1024];
                int recvSize = recv(*Iter, buff, 1024, MSG_NOSIGNAL);

                if ((recvSize == 0) && (errno != EAGAIN))
                {
                    shutdown(*Iter, SHUT_RDWR);
                    close(*Iter);
                    _clientSocketList.erase(Iter);
                }
                else if (recvSize != 0)
                {
                    send(*Iter, buff, recvSize, MSG_NOSIGNAL);
                }
            }
        }
        if (FD_ISSET(_masterSocket._socketFD, &sett))
        {
            int     clientSocket = accept(_masterSocket._socketFD, 0, 0);
            setNonBlock(clientSocket);
            _clientSocketList.insert(clientSocket);
        }
        
        int clientSocket = accept(_masterSocket._socketFD, 0, 0);
        int buff[5] = {0, 0, 0, 0, 0};
        recv(clientSocket, buff, 4, MSG_NOSIGNAL);
        shutdown(clientSocket, SHUT_RDWR);
        close(clientSocket);
        //std::cout << buff[0] << std::endl;
        printf("%s\n", buff);
        */
       
    }
}
/*
Server::Server( const std::string &configFilePath )
{
    // parse config file here
    

}
*/
Server::~Server( void ) {}