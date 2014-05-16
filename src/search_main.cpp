/*
 * search_main.cpp
 *
 *  Created on: May 14, 2014
 *      Author: wang
 */

#include "Socket.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#define MAXRECV 1024
int main(int argc, char**argv)
{
	Conf conf(argv[1]);
	std::string ip, port ;
	ip = conf.get_value("Socket_ip");
	port = conf.get_value("Socket_port") ;
	Socket socket(ip, port) ;
	socket.Socket_listen();  //监听
	pid_t pid ;
	int socket_fd = socket.get_socket();

	//监听设置
	fd_set fd_rd, fd_rd_back;
	struct timeval tm;
	FD_SET(socket_fd, &fd_rd);
	tm.tv_sec = 1;
	tm.tv_usec = 0 ;
	char recv_buf[MAXRECV];  //用于接收
	/*
	while(true){
		fd_rd_back = fd_rd;
		select(1024, &fd_rd_back, NULL, NULL, &tm);
		memset(recv_buf, 0, MAXRECV);
		//监听到客户端发送过来的请求
		if(FD_ISSET(socket_fd, &fd_rd_back))
		{
			std::cout<<"ok select"<<std::endl;
	*/
			int client_fd ;
			while(-1 != (client_fd = socket.Socket_accept()))
			{
				pid = fork();    //创建进程
				if(pid < 0 )
				{
					perror("fork");
					break;
				}
				else if(pid > 0) //父进程
				{
					close(client_fd);
					pid_t iret ;
					iret = waitpid(-1, NULL, WNOHANG);
					if(iret > 0 )
					{
						std::cout<<"iret: "<<iret <<std::endl;
					}
					//exit(0);
				}
				else   //子进程，用于处理逻辑
				{
					std::cout<<"it is child"<<std::endl;

					int ired = 0 ;
					ired = recv(client_fd, recv_buf, (std::size_t)1024, 0);
					std::cout<<"receive message: "<<recv_buf<<" the length: "<<ired<<std::endl;

					std::string jsonstr = socket.json_string();   //转换成json格式
					std::cout<<"json string: "<<jsonstr<<std::endl;

					ired = send(client_fd, jsonstr.c_str(), jsonstr.size(), 0) ;
					std::cout<<"send ired: "<<ired<<std::endl;

					close(client_fd);
					exit(0);
				}
			}
	//	}
	//}

	return 0 ;
}


