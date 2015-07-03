//
//  Complete_Notice.cpp
//  librdmaemu
//
//  Created by Tyler on 6/17/15.
//  Copyright (c) 2015 Tyler. All rights reserved.
//

#include "Complete_Notice.h"

CompleteNotice::CompleteNotice(){
    wr_id = -1;
    //data = NULL;
    size = 0;
    socket_fd = -1;
}

CompleteNotice::CompleteNotice(int _socket_fd, int _wr_id, int _size){
    socket_fd = _socket_fd;
    wr_id = _wr_id;
    //data = _data;
    size = _size;
    bzero(data, 128);
}

CompleteNotice::~CompleteNotice(){
    
}

void CompleteNotice::setData(char _data,int _size){
    //std::cout << "XXXXXXX\n";
    /*for (int i = 0; i < _size; i ++) {
        //std::cout << "XXXXXXX\n";
        data[i] = _data[i];
        std::cout << data[i];
    }*/
    memcpy(data, &_data, sizeof(_data));
}

void CompleteNotice::setDataByIndex(int index, int value){
    data[index] = value;
}


