//
//  RDMA_Server.cpp
//  rdmaemu
//
//  Created by Tyler on 6/17/15.
//  Copyright (c) 2015 Tyler. All rights reserved.
//

#include "RDMA_Server.h"

void *sendThreadMsg(void* msg);
int ACKFlag = 1;
int msgcount = 0;

RDMAServer::RDMAServer(int port){
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cout << "Error open server socket\n";
    }
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);
}

RDMAServer::~RDMAServer(){
    
}

int RDMAServer::bindAddress(){
    int ret = bind(server_fd, (struct sockaddr*)(&server_addr), sizeof(server_addr));
    return ret;
}

void RDMAServer::listenSocket(int max){
    listen(server_fd, max);
}

void RDMAServer::wait4Connection(){
    std::cout << "Wait for connection ...\n";
    int addrlen = sizeof(server_addr);
    int newsock_fd = accept(server_fd, (struct sockaddr*)&server_addr, (socklen_t*)&addrlen);
    if (newsock_fd < 0) {
        std::cout << "Error new sock\n";
    }
    std::cout << "connected\n";
    newsocket_fd = newsock_fd;
    char buff[10];
    bzero(buff, 10);
    /*recv(newsocket_fd, buff, 10,0);
    std::cout << buff << std::endl;
    send(newsocket_fd, "ROGER", 10,0);*/
}

void RDMAServer::recvMsg(){
    char buff[MAX_BUFFER_SIZE];
    bzero(buff, MAX_BUFFER_SIZE);
    /*int n;
    n = read(_sock_fd, buff, MAX_BUFFER_SIZE);
    if (n < 0) {
        std::cout << "Error Reading from buff\n";
    }*/
    recv(newsocket_fd,buff,MAX_BUFFER_SIZE,0);
    std::cout << buff << std::endl;
    send(newsocket_fd, "I got your msg", 100, 0);
}

/*
 return value -1 : None left work request
 return value  0 : suceed
 */
int RDMAServer::eventHandler(){
    WorkRequest* wr = wq.getWorkRequest();
    if (wr == NULL) {
        return -1;
    }
    CompleteNotice* cn;
    if (wr->getType() == RDMA_READ) {
        //std::cout << "XX\n";
        wr->readData(sharedMem);
        cn = new CompleteNotice(newsocket_fd, wr->getWorkRequestId(), wr->getSize());
        for (int i = 0; i < wr->getSize(); i ++) {
            cn->data[i] = wr->data[i];
        }
        sendNotice(cn);
        wq.removeWork();
        cq.addCompleteWork(*wr);
    }
    else if (wr->getType() == RDMA_WRITE){
        wr->writeData(sharedMem);
        cn = new CompleteNotice(newsocket_fd, wr->getWorkRequestId(), wr->getSize());
        sendNotice(cn);
        wq.removeWork();
        cq.addCompleteWork(*wr);
    }
    return 0;
}

/*
CompleteNotice RDMAServer::RDMAReadHandler(WorkRequest* wr){
    CompleteNotice cn(server_fd, wr->getWorkRequestId(),wr->readData(sharedMem),wr->getSize());
    return cn;
}

CompleteNotice RDMAServer::RDMAWriteHandler(WorkRequest* wr){
    CompleteNotice cn(server_fd, wr->getWorkRequestId(), NULL, wr->getSize());
    return cn;
}*/

void RDMAServer::sendNotice(CompleteNotice* cn){
    while (ACKFlag <= 0);
    ACKFlag --;
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, sendThreadMsg, cn);
}

void RDMAServer::processWorkRequest(){
    while (1) {
        if (msgcount < capacity) {
            continue;
        }
        int ehret = eventHandler();
        if(ehret < 0){
            //std::cout << ehret << std::endl;
            //Sleep(500);
            continue;
        }
    }
}

void *sendThreadMsg(void* msg){
    CompleteNotice* cn = (CompleteNotice*)msg;
    send(cn->getSocketFd(), cn, sizeof(*cn), 0);
    return NULL;
}

struct arg{
    WorkQueue* wq;
    int newsocket_fd;
};

void *recv(void* argv){
    struct arg* tmp=(struct arg*)argv;
    int sock_fd = tmp->newsocket_fd;
    WorkQueue* wq = tmp->wq;
    while(1)
    {
        char request[1024];
        ssize_t result = recv(sock_fd,request,1024,0);
        if(result > 0)
        {
            if(!strcmp(request,"ACK")){ACKFlag++;}
            else{
                msgcount ++;
                send(sock_fd,"ACK",sizeof("ACK"),0);
                WorkRequest wr=*(WorkRequest*)request;
                std::cout << "\nReceived Work Request #" << wr.getWorkRequestId() << std::endl;
                wq->addWork(wr);
                if(wq->getWorkRequest() == NULL)
                    std::cout << "NULL";
                    
            }
        }
    }
}

void RDMAServer::recvWR(){
    pthread_t id;
    struct arg* argv = new arg();
    argv->newsocket_fd = newsocket_fd;
    argv->wq = &wq;
    pthread_create(&id, NULL, recv, (void*)argv);
}




