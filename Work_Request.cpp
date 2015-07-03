//
//  Work_Request.cpp
//  rdmaemu
//
//  Created by Tyler on 6/16/15.
//  Copyright (c) 2015 Tyler. All rights reserved.
//

#include "Work_Request.h"

int WorkRequest::idcount = 0;

WorkRequest::WorkRequest(){
    type = NOWORK;
    idcount ++;
    wr_id = idcount;
    isFinshied = false;
    //data = NULL;
}

/*
WorkRequest::WorkRequest(WorkTypes _type, int _id){
    type = _type;
    wr_id ++;
    isFinshied = false;
}*/

WorkRequest::~WorkRequest(){
    
}

WorkRequest::WorkRequest(WorkTypes _type, int _startPoint, int _size){
    idcount ++;
    wr_id = idcount;
    type = _type;
    //data = _data;
    startPoint = _startPoint;
    size = _size;
}

/*
 return value -2 : Error false false
 return value -1 : Error true true
 return value  0 : Error Unknown
 return value  1 : set finished
 return value  2 : set unfinished
*/

int WorkRequest::setFinishedFlag(bool flag){
    if (isFinshied == false && flag == false) {
        return -2;
    }
    else if(isFinshied == true && flag == true){
        return 1;
    }
    else if(isFinshied == false && flag == true){
        isFinshied = true;
        return 1;
    }
    else if(isFinshied == true && flag == false){
        isFinshied = false;
        return 2;
    }
    
    return 0;
}

void WorkRequest::readData(RDMAMem &m){
    if (type == RDMA_READ) {
        m.Read_Mem(data, startPoint, size);
        /*for (int i = 0; i < size ; i ++) {
            std::cout << data[i];
        }*/
    }
    else
        return;
}

int WorkRequest::writeData(RDMAMem &m){
    if (type == RDMA_WRITE) {
        return m.Write_Mem(data, startPoint, size);
    }
    else
        return -1;
}
