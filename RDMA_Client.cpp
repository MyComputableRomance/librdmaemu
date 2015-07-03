//
//  RDMA_Client.cpp
//  librdmaemu
//
//  Created by Tyler on 6/17/15.
//  Copyright (c) 2015 Tyler. All rights reserved.
//

#include "RDMA_Client.h"

int ACKFlag = 0;

struct argc{
    int socket_fd;
    RDMAClient* rdmaclient;
};

void *poll(void* argv){
    struct argc* tmp = (struct argc*)argv;
    RDMAClient* rdmac = tmp->rdmaclient;
    int sock_fd = tmp->socket_fd;
    while(1)
    {
        char notice[1024];
        ssize_t result = recv(sock_fd,notice,1024,0);
        
        //printf("recieve: %d\n",result);
        if(result > 0)
        {
            //printf("recieve: %d\n",result);
            if(!strcmp(notice,"ACK")){ACKFlag++; std::cout << "    ACK\n";}
            else{
                //printf("notice\n");
                send(sock_fd,"ACK",sizeof("ACK"),0);
                CompleteNotice cn = *(CompleteNotice*)notice;
                //std::cout << "XXXX";
                rdmac->processCN(cn);
            }//printf("success\n");
        }
    }
}

RDMAClient::RDMAClient(){
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        std::cout << "Error open client socket\n";
    }
    bzero(&client_addr, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    
    sendIndex = 0;
}

RDMAClient::~RDMAClient(){

}

bool RDMAClient::connect2server(char* server_addr, int port){
    client_addr.sin_port = htons(port);
    client_addr.sin_addr.s_addr = inet_addr(server_addr);
    if (connect(socket_fd, (sockaddr*)&client_addr, sizeof(client_addr))) {
        return false;
    }
    return true;
}

ssize_t RDMAClient::sendWorkRequest(WorkRequest wr){
    std::cout << "Sending Work Request #" << wr.getWorkRequestId();
    ssize_t result = send(socket_fd, (void*)&wr, sizeof(wr), 0);
    if(result > 0){
        while (ACKFlag <= 0);
        ACKFlag --;
    }
    return result;
}

int RDMAClient::sendWorkRequestByIndex(){
    std::cout << "Sending Work Request By Index "<< sendIndex;
    WorkRequest* wr = wq.getWorkRequestByIndex(sendIndex);
    if(wr == NULL){
        return 0;
    }
    else{
        size_t result = send(socket_fd, (void*)wr, sizeof(&wr), 0);
        if (result > 0) {
            while (ACKFlag <= 0);
            ACKFlag --;
        }
        sendIndex ++;
        return 1;
    }
}

void RDMAClient::addWorkRequest2Queue(WorkRequest wr){
    wq.addWork(wr);
}

ssize_t RDMAClient::sendMsgs(char *msg, int _size){
    return send(socket_fd,(void*)&msg,_size,0);
}

void RDMAClient::sendStdIn(){
    char buff[100];
    std::cout << "Enter Msg: ";
    bzero(buff, 100);
    fgets(buff, 100, stdin);
    if(send(socket_fd, (void*)buff, strlen(buff), 0) < 0)
        std::cout << "Error send stdin\n";
    bzero(buff, 100);
    if(recv(socket_fd, buff, 100, 0) < 0)
        std::cout << "Error recv stdin\n";
    std::cout << buff;    
}

int RDMAClient::processCN(CompleteNotice cn){
    WorkRequest* wr = wq.getWorkRequest();
    if (cn.getWRId() != wr->getWorkRequestId()) {
        return -1;
    }
    std::cout << "Work Request #" << wr->getWorkRequestId() << " Completed!\n";
    std::cout << "Work Type : ";
    if (wr->getType() == RDMA_READ) {
        std::cout << "RDMA_READ\n";
        wr->setFinishedFlag(true);
        std::cout << "Read Server Shared Memory From " << wr->getStartPoint() << ", Size "<< wr->getSize() << std::endl;
        for (int i = 0; i < wr->getSize(); i ++) {
            //wr->data[i] = cn.data[i];
            std::cout << cn.data[i];
        }
        std::cout << std::endl;
    }
    else if (wr->getType() == RDMA_WRITE) {
        std::cout << "RDMA_WRITE\n";
        wr->setFinishedFlag(true);
        std::cout << "Write Server Shared Memory From " << wr->getStartPoint() << ", Size " << wr->getSize() << std::endl;
        //printf("%s",wr->data);
        for (int i = 0; i < wr->getSize(); i ++) {
            std::cout << wr->data[i];
        }
        std::cout << std::endl;
    }
    wq.removeWork();
    cq.addCompleteWork(*wr);
    return 0;
}

void RDMAClient::pollCQ(){
    pthread_t id;
    struct argc* argcv = new argc();
    argcv->socket_fd = socket_fd;
    argcv->rdmaclient = this;
    pthread_create(&id, NULL, poll, (void*)argcv);
}


