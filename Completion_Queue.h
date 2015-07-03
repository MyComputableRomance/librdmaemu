//
//  Completion_Queue.h
//  rdmaemu
//
//  Created by Tyler on 6/16/15.
//  Copyright (c) 2015 Tyler. All rights reserved.
//

#ifndef Completion_Queue_H
#define Completion_Queue_H

#include <stdio.h>
#include <list>
#include "Work_Request.h"
//#include "RDMA_Read.h"
//#include "RDMA_Write.h"

//using namespace std;

class CompletionQueue {
private:
    std::list<WorkRequest>* cql;
public:
    CompletionQueue();
    ~CompletionQueue();
    
    int addCompleteWork(WorkRequest wr);
    void removeTopWork();
};

#endif /* defined(__rdmaemu__Completion_Queue__) */
