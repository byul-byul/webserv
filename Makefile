SERVER_NAME	=	webserv
CLIENT_NAME	=	client

SRCS		=	./srcs/main.cpp \
				./srcs/Server.cpp \
				./srcs/Socket.cpp 

all: buildServer

buildServer:
	c++ -o $(SERVER_NAME) $(SRCS)

buildClient:
	c++ -o $(CLIENT_NAME)