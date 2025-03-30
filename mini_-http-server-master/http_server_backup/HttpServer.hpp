#pragma once

#include <iostream>
#include <pthread.h>
#include <signal.h>

#include "Log.hpp"
#include "TcpServer.hpp"
#include "Task.hpp"
#include "ThreadPool.hpp"

#define PORT 8081

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
