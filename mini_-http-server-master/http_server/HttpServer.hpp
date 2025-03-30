#pragma once

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

#include "Log.hpp"
#include "Task.hpp"
#include "ThreadPool.hpp"

#define BACKLOG 5
#define PORT 8081

class TcpServer{
    private:
        int port;
        int listen_sock;
        static TcpServer *svr;
    private:
        TcpServer(int _port):port(_port),listen_sock(-1)
        {}
        TcpServer(const TcpServer &s){}
    public:
        static TcpServer *getinstance(int port)//单例模式
        {
            static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
            if(nullptr == svr){
                pthread_mutex_lock(&lock);
                if(nullptr == svr){
                    svr = new TcpServer(port);
                    svr->InitServer();
                }
                pthread_mutex_unlock(&lock);
            }
            return svr;
        }
        void InitServer()
        {
            Socket();//创建套接字
            Bind(); //绑定（本地端口号）
            Listen();//监听
            LOG(INFO, "tcp_server init ... success");
        }
        void Socket()
        {
            listen_sock = socket(AF_INET, SOCK_STREAM, 0);
            if(listen_sock < 0){
                LOG(FATAL, "socket error!");
                exit(1);
            }
            int opt = 1;
            setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
            LOG(INFO, "create socket ... success");
        }
        void Bind()
        {
            struct sockaddr_in local;
            memset(&local, 0, sizeof(local));
            local.sin_family = AF_INET;
            local.sin_port = htons(port);
            local.sin_addr.s_addr = INADDR_ANY; //云服务器不能直接绑定公网IP

            if(bind(listen_sock, (struct sockaddr*)&local, sizeof(local)) < 0){
                LOG(FATAL, "bind error!");
                exit(2);
            }
            LOG(INFO, "bind socket ... success");
        }
        void Listen()
        {
            if(listen(listen_sock, BACKLOG) < 0){
                LOG(FATAL, "listen socket error!");
                exit(3);
            }
            LOG(INFO, "listen socket ... success");
        }
        int Sock()
        {
            return listen_sock;
        }
        ~TcpServer()
        {
            if(listen_sock >= 0) close(listen_sock);
        }
};
TcpServer* TcpServer::svr = nullptr;

class HttpServer{
    private:
        int port;
        bool stop;
    public:
        HttpServer(int _port = PORT): port(_port),stop(false)
        {}
        void InitServer()
        {
            //信号SIGPIPE需要进行忽略，如果不忽略，在写入时候，断开连接的话，可能直接崩溃server
            signal(SIGPIPE, SIG_IGN); 
        }
        void Loop()
        {
            TcpServer *tsvr = TcpServer::getinstance(port);//这里已经完成了创建套接字、绑定、监听
            LOG(INFO, "Loop begin");
            while(!stop){
                struct sockaddr_in peer;
                socklen_t len = sizeof(peer);
                int sock = accept(tsvr->Sock(), (struct sockaddr*)&peer, &len);//获取新连接
                if(sock < 0){
                    continue;
                }
                LOG(INFO, "Get a new link");
				
                Task task(sock);//获取新连接之后，创建一个任务task
                ThreadPool::getinstance()->PushTask(task); //把该任务push进线程池，让一个新线程来处理它
            }
        }
        ~HttpServer()
        {}
};
