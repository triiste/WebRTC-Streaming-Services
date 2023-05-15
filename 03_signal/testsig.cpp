#include<iostream>

#include<signal.h> //信号头文件
#include<unistd.h> //暂停信号

void sighandle(int sig){
    std::cout<<"receved signal: ..."
            <<sig
            <<std::endl;
}

int main(int argc,char * argv[]){
    signal(SIGINT,sighandle);//ctrl+c 代号为2
    signal(SIGQUIT,sighandle);//安装信号 捕获 ctrl+\ 代号为3 
    signal(SIGHUP,sighandle); //终端结束 代号为1
    pause(); //程序暂停
    return 0;

}
