//
//  Work_Queue.h
//  rdmaemu
//
//  Created by Tyler on 6/16/15.
//  Copyright (c) 2015 Tyler. All rights reserved.
//

#ifndef Work_Queue_H
#define Work_Queue_H

#include <stdio.h>
#include <list>
#include "Work_Request.h"
//#include "RDMA_Read.h"
//#include "RDMA_Write.h"

//using namespace std;

class WorkQueue {
private:
    std::list<WorkRequest>* wql;
    std::list<WorkRequest>::iterator it;
public:
    WorkQueue();
    ~WorkQueue();
    
    WorkRequest* getWorkRequest();
    WorkRequest* getWorkRequestByIndex(int index);
    void addWork(WorkRequest wr);
    void removeWork();
    size_t getWQLSize(){ return wql->size(); };
    //WorkRequest getByIndex(int index);
};

#endif /* defined(__rdmaemu__Work_Queue__) */
