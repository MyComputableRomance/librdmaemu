//
//  RDMA_Mem.cpp
//  rdmaemu
//
//  Created by Tyler on 6/15/15.
//  Copyright (c) 2015 Tyler. All rights reserved.
//
#include "RDMA_Mem.h"

int RDMAMem::fdcount = 0;

RDMAMem::RDMAMem(){
    fdcount ++;
    mem_fd = fdcount;
    bzero(mem_region, MAX_BUFFER_SIZE);
}

RDMAMem::~RDMAMem(){
}

/*
 return value -1: Out Of Memory Region
 return value 0 : Succeed
 */
int RDMAMem::Write_Mem(char* data, int startPoint, int size){
    for(int i = 0;i < size; i ++){
        mem_region[startPoint + i] = data[i];
        //std::cout << " " << mem_region[startPoint + i];
    }
    /*for (int i = 0; i < 1024; i ++) {
        std::cout << mem_region[i];
    }*/
    return 0;
}

void RDMAMem::Read_Mem(char* data, int startPoint, int size){
    if(startPoint + size >= MAX_BUFFER_SIZE)
        return;
    
    //memcpy(data, &mem_region[startPoint], size);
    for (int i = 0; i < size; i ++) {
        data[i] = mem_region[startPoint + i];
        //std::cout << data[i];
    }
}

void RDMAMem::Clear_Mem(){
    bzero(mem_region, MAX_BUFFER_SIZE);
}

int RDMAMem::getMemFd(){
    return mem_fd;
}

void RDMAMem::printMem(){
    for(int i = 0; i < MAX_BUFFER_SIZE; i ++){
        std::cout << mem_region[i];
    }
}