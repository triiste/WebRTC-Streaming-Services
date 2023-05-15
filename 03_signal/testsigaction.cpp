#include<iostream>
#include<signal.h> //跟信号有关的头文件
#include<unistd.h> //暂停

void sighandler(int sig){
    std::cout<<"received signal:"
            <<sig
            <<std::endl;
}
int main(int argc, char* argv[]){
    struct sigaction act,oact;
    act.sa_handler = sighandler;
    sigfillset(&act.sa_mask);
    act.sa_flags = 0 ;
    sigaction(SIGINT,&act,&oact); //SIGINT 代号为2

    pause();
    return 0;
}
