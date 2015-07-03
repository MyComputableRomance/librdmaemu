//
//  Work_Queue.cpp
//  rdmaemu
//
//  Created by Tyler on 6/16/15.
//  Copyright (c) 2015 Tyler. All rights reserved.
//

#include "Work_Queue.h"

WorkQueue::WorkQueue(){
    wql = new std::list<WorkRequest>();
    it = wql->begin();
}

WorkQueue::~WorkQueue(){
    delete wql;
}

void WorkQueue::addWork(WorkRequest wr) {
    wql->push_back(wr);
}

void WorkQueue::removeWork(){
    wql->front().setFinishedFlag(true);
    wql->pop_front();
}

WorkRequest* WorkQueue::getWorkRequest(){
    if (wql->empty()) {
        return NULL;
    }
    else
        return &wql->front();
}

WorkRequest* WorkQueue::getWorkRequestByIndex(int index){
    if (wql->size() > index) {
        it = std::next(wql->begin(),index);
        return &*it;
    }
    return NULL;
}

/*WorkRequest WorkQueue::getByIndex(int index){
    int t = index;
    std::list<WorkRequest>::iterator it = wql->begin();
    while (t > 0) {
        it ++;
        t --;
    }
    return *it;
}*/
