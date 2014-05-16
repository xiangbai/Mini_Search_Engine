/*
 * Socket.h
 *
 *  Created on: May 14, 2014
 *      Author: wang
 */

/*
 * TCP协议，面向有连接的可靠通信
 * socket-->bind-->listen-->accept-->recv/recvfrom-->send/sendto
 */
#ifndef SOCKET_H_
#define SOCKET_H_
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <stdexcept>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/wait.h>
#include "json/json.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#define BUF_SIZE 1024
class Socket {
public:
	Socket();  //socket,bind

	void Socket_listen();  //listen
	int Socket_accept();  //accept
	int get_socket()const ;
	std::string json_string() ; //转换成json格式
	virtual ~Socket();    //close socket
private:
	int _socket_fd ;
	struct sockaddr_in m_server_addr ;
};

#endif /* SOCKET_H_ */
