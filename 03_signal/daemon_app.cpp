#include<iostream>

#include<unistd.h>
#include<stdlib.h>

int main(int argc,char* argv[]){
    if(daemon(0,0) == -1)// nochdir 设为0是改变目录  noclose //设为0 重定向标准文件
    {
        std::cout<<"error\n"<<std::endl;
        exit(-1);
    }
    while(1){
        sleep(1);
    }

}



