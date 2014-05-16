/*
 * Socket.cpp
 *
 *  Created on: May 14, 2014
 *      Author: wang
 */

#include "Socket.h"
#include <iostream>

Socket::Socket(const std::string &ip, const std::string &port):_socket_fd(0){
	// TODO Auto-generated constructor stub
	if(-1 == (_socket_fd = socket(AF_INET, SOCK_STREAM, 0)))
	{
		perror("socket");
		exit(-1);
	}
	memset(&m_server_addr, 0, sizeof(struct sockaddr_in));

	//需要重置端口号
	//设置端口号重用
	bool bReuseaddr=true;
	setsockopt(_socket_fd,SOL_SOCKET,SO_REUSEADDR,(char*)&bReuseaddr,sizeof(bool));

	m_server_addr.sin_family = AF_INET ;
	/*
	 * 此处需要读取配置文件，以获取端口号和IP地址
	 */
	m_server_addr.sin_port = htons(atoi(port.c_str()));
	m_server_addr.sin_addr.s_addr = inet_addr(ip.c_str());

	int reuse = 1 ;
	int buf_num = BUF_SIZE;
	if(0 != setsockopt(_socket_fd, SOL_SOCKET, SO_REUSEADDR,  (void*)&reuse, sizeof(int)) )
	{
		close(_socket_fd);
		exit(0);
	}
	if(0 != setsockopt(_socket_fd, SOL_SOCKET, SO_SNDBUF,  (void*)&buf_num, sizeof(int)) )
	{
		close(_socket_fd);
		exit(0);
	}
	if(0 != setsockopt(_socket_fd, SOL_SOCKET, SO_RCVBUF,  (void*)&buf_num, sizeof(int)) )
	{
		close(_socket_fd);
		exit(0);
	}

	if(-1 == bind(_socket_fd, (struct sockaddr *)&m_server_addr, sizeof(struct sockaddr_in)))
	{
		perror("bind");
		close(_socket_fd);
		exit(1);
	}
}
void Socket::Socket_listen()
{
	if(-1 == listen(_socket_fd, 10))
	{
		perror("listen");
		close(_socket_fd);
		exit(1);
	}
}
int Socket::Socket_accept(){
	int client_fd ;
	if(-1 == (client_fd = accept(_socket_fd, NULL, NULL)))
	{
		perror("accept");
		close(_socket_fd);
		exit(1);
	}
	std::cout<<"accept: "<<client_fd<<std::endl;
	return client_fd ;
}
int Socket::get_socket()const{
	return _socket_fd ;
}


std::string Socket::json_string()
{
	srand(time(NULL));
	int size ;
	while(1)
	{
		size = 50;//rand() % 100 ;
		if(size > 0)
		{
			break ;
		}
	}
	Json::Value root ;
	Json::Value arr ;
	while(size)
	{
		Json::Value elem ;
		char title[128] = "";
		char summary[128]="";
		sprintf(title , "tile_%d", size);
		sprintf(summary, "summary_%d", size);
		elem["title"] = title ;
		elem["summary"] = summary ;
		arr.append(elem);
		size -- ;
	}
	root["files"]=arr ;
	Json::FastWriter writer ;
	Json::StyledWriter stlwriter ;
	return stlwriter.write(root);

}
Socket::~Socket() {
	// TODO Auto-generated destructor stub
	close(_socket_fd);
}

