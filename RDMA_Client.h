//
//  RDMA_Client.h
//  librdmaemu
//
//  Created by Tyler on 6/17/15.
//  Copyright (c) 2015 Tyler. All rights reserved.
//

#ifndef RDMA_Client_H
#define RDMA_Client_H

#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "Work_Request.h"
#include "RDMA_Mem.h"
#include "Work_Queue.h"
#include "Complete_Notice.h"
#include "Completion_Queue.h"

class RDMAClient {
private:
    int socket_fd;
    sockaddr_in client_addr;
    WorkQueue wq;
    CompletionQueue cq;
    int sendIndex;
public:
    RDMAClient();
    ~RDMAClient();
    bool connect2server(char* server_addr, int port);
    void sendStdIn();
    void addWorkRequest2Queue(WorkRequest wr);
    size_t getWQSize(){ return wq.getWQLSize(); };
    //WorkRequest getWRbyIndex(int index){ return wq.getByIndex(index); };
    
    ssize_t sendMsgs(char *msg ,int size);
    ssize_t sendWorkRequest(WorkRequest wr);
    int sendWorkRequestByIndex();
    //void recvCompleteNotice();
    int processCN(CompleteNotice cn);
    void pollCQ();
};

#endif /* defined(__librdmaemu__RDMA_Client__) */
