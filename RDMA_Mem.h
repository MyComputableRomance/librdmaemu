//
//  RDMA_Mem.h
//  rdmaemu
//
//  Created by Tyler on 6/15/15.
//  Copyright (c) 2015 Tyler. All rights reserved.
//

#ifndef RDMA_MEM_H
#define RDMA_MEM_H


#include <stdio.h>
#include <iostream>
#include <cstring>

//using namespace std;

#define MAX_BUFFER_SIZE 1024


class RDMAMem{
private:
    int mem_fd;
    char mem_region[MAX_BUFFER_SIZE];
    static int fdcount;
public:
    RDMAMem();
    //RDMA_Mem(int fd);
    ~RDMAMem();
    
    void printMem();
    int Write_Mem(char* data, int startPoint, int size);
    void Read_Mem(char* data, int startPoint, int size);
    
    void Clear_Mem();
    
    int getMemFd();
    int getValidSize(){ return strlen(mem_region); };
    char getMemByIndex(int index){ return mem_region[index]; };
};
    
#endif