//
//  Work_Request.h
//  rdmaemu
//
//  Created by Tyler on 6/16/15.
//  Copyright (c) 2015 Tyler. All rights reserved.
//

#ifndef WORK_REQUEST_H
#define WORK_REQUEST_H

#include <stdio.h>
#include "Work_Types.h"
#include "RDMA_Mem.h"

/*
 type value 0 : SEND
 type value 1 : RECV
 type value 2 : RDMA_SEND
 type value 3 : RDMA_RECV
*/

class WorkRequest{
protected:
    WorkTypes type;
    int wr_id;
    bool isFinshied;
    
    int startPoint;
    int size;
    
    static int idcount;
    
public:
    WorkRequest();
    //WorkRequest(WorkTypes _type, int _id);
    WorkRequest(WorkTypes _type, int _startPoint, int _size);
    ~WorkRequest();
    
    char data[128];
    WorkTypes getType() { return type; };
    bool getFinshedFlag() { return isFinshied; };
    int getWorkRequestId(){ return wr_id; };
    int getSize(){ return size; };
    int getStartPoint() { return startPoint; };
    //char* getData() { return data; };
    int setFinishedFlag(bool flag);
    
    void readData(RDMAMem& m);
    int writeData(RDMAMem& m);
};

#endif /* defined(WORK_REQUEST_H) */
