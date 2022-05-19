SERVER_NAME	=	webserv

SRCS		=	./srcs/main.cpp \
				./srcs/Server.cpp \
				./srcs/Socket.cpp 

all: buildServer

buildServer:
	c++ -o $(SERVER_NAME) $(SRCS)
