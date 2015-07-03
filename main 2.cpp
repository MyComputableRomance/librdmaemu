//
//  main.cpp
//  RDMATestClient
//
//  Created by Tyler on 6/17/15.
//  Copyright (c) 2015 Tyler. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include "RDMA_Client.h"

int main(int argc, const char * argv[]) {
    
    RDMAClient rc;
    char x[100] = "127.0.0.1";
    bool t = rc.connect2server(x,1228);
    if( t == false) {
        return -1;
    }
    rc.pollCQ();
    WorkRequest wr1(RDMA_WRITE, 0, 80);
    WorkRequest wr2(RDMA_WRITE, 41, 40);
    WorkRequest wr3(RDMA_WRITE, 31, 20);
    WorkRequest wr4(RDMA_READ, 30, 40);
    WorkRequest wr5(RDMA_WRITE,10,10);
    WorkRequest wr6(RDMA_READ, 10, 60);
    for (int i = 0; i < 128; i ++) {
        wr1.data[i] = '0';
        wr2.data[i] = '1';
        wr3.data[i] = '2';
        wr5.data[i] = '5';
    }
    rc.addWorkRequest2Queue(wr1);
    rc.sendWorkRequest(wr1);
    //rc.sendWorkRequestByIndex();
    
    rc.addWorkRequest2Queue(wr2);
    rc.sendWorkRequest(wr2);
    //rc.sendWorkRequestByIndex();
    
    rc.addWorkRequest2Queue(wr3);
    rc.sendWorkRequest(wr3);
    //rc.sendWorkRequestByIndex();
    
    rc.addWorkRequest2Queue(wr4);
    rc.sendWorkRequest(wr4);
    //rc.sendWorkRequestByIndex();
    
        pthread_exit(NULL);
    return 0;
}
