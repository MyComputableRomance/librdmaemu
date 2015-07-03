//
//  main.cpp
//  librdmaemu
//
//  Created by Tyler on 6/17/15.
//  Copyright (c) 2015 Tyler. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include "RDMA_Server.h"

int main(int argc, const char * argv[]) {
    //std::cout << sizeof("ACK");
    
    RDMAServer rs(1228);
    if(rs.bindAddress() < 0){
        std::cout << "OCUPPY";
        return -1;
    }
    rs.setCapacity(4);
    rs.listenSocket(1);
    rs.wait4Connection();
    rs.recvWR();
    //cout << count;
    rs.processWorkRequest();
    //std::cout << rs.getWQSize() << std::endl;
    pthread_exit(NULL);
    
    std::cout << "Hello, World!\n";
    return 0;
}
