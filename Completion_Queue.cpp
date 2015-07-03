//
//  Completion_Queue.cpp
//  rdmaemu
//
//  Created by Tyler on 6/16/15.
//  Copyright (c) 2015 Tyler. All rights reserved.
//

#include "Completion_Queue.h"

CompletionQueue::CompletionQueue(){
    cql = new std::list<WorkRequest>();
}

CompletionQueue::~CompletionQueue(){
    delete cql;
}

/*
 return value -1 : unfinished work request
 return value  0 : succeed
 */

int CompletionQueue::addCompleteWork(WorkRequest wr){
    if (!wr.getFinshedFlag()) {
        return -1;
    }
    cql->push_back(wr);
    return 0;
}

void CompletionQueue::removeTopWork(){
    cql->pop_front();
}