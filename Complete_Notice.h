//
//  Complete_Notice.h
//  librdmaemu
//
//  Created by Tyler on 6/17/15.
//  Copyright (c) 2015 Tyler. All rights reserved.
//

#ifndef Complete_Notice_H
#define Complete_Notice_H

#include <stdio.h>
#include "Work_Request.h"
//#include "RDMA_Write.h"
//#include "RDMA_Read.h"

class CompleteNotice {
private:
    int wr_id;
    int size;
    int socket_fd;
public:
    CompleteNotice();
    CompleteNotice(int _socket_fd, int _wr_id, int _size);
    ~CompleteNotice();
    
    char data[128];
    void setData(char _data,int size);
    int getSocketFd(){ return socket_fd; };
    char* getData(){ return data; };
    int getSize(){ return size; };
    int getWRId(){ return wr_id; };
    void setDataByIndex(int index,int value);
};

#endif /* defined(__librdmaemu__Complete_Notice__) */
