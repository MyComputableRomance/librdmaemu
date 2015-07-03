//
//  RDMA_Server.h
//  rdmaemu
//
//  Created by Tyler on 6/17/15.
//  Copyright (c) 2015 Tyler. All rights reserved.
//

#ifndef RDMA_Server_H
#define RDMA_Server_H

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#include "RDMA_Mem.h"
#include "Work_Request.h"
//#include "RDMA_Read.h"
//#include "RDMA_Write.h"
#include "Work_Queue.h"
#include "Completion_Queue.h"
#include "Complete_Notice.h"

class RDMAServer {
private:
    int server_fd;
    sockaddr_in server_addr;
    int connectionCount;
    RDMAMem sharedMem;
    int newsocket_fd;
    
    WorkQueue wq;
    CompletionQueue cq;
    
    int msgleft;
    int capacity;
public:
    RDMAServer(int port);
    ~RDMAServer();
    int bindAddress();
    void listenSocket(int max = 10);
    void wait4Connection();
    RDMAMem getSharedMem(){ return sharedMem; };
    void recvMsg();
    void recvWR();
    int getWQSize(){ return wq.getWQLSize(); };
    
    void processWorkRequest();
    
    int eventHandler();
    //CompleteNotice RDMAReadHandler(WorkRequest* wr);
    //CompleteNotice RDMAWriteHandler(WorkRequest* wr);
    void sendNotice(CompleteNotice* cn);
    void printMemory(){ sharedMem.printMem();};
    
    int getCapacity() {return capacity;};
    void setCapacity(int _capacity) { capacity = _capacity;};
};

#endif /* defined(__rdmaemu__RDMA_Server__) */
