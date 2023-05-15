#include<iostream>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>

void daemonize(){
    //4步
    //fork创建一个子进程，父进程退出，子进程成为孤儿进程 被init进程接管
    //调用setid建立新的进程会话
    //将当前工作目录切换到根目录
    //将标准输入输出 出错重定向到 /dev/null
    pid_t pid;
    if((pid = fork()) < 0){ 
        std::cout<<"can't create suprocess!"<<std::endl;
    }else{
        if(pid != 0){
            exit(0);//创建了子进程 父进程退出就好了 保证了只有子进程 子进程是个孤儿进程
        }
    }
    setsid(); //第二步
    if(chdir("/") < 0){
        std::cout<<"can't change dir"<<std::endl;
        exit(-1);//此时说明出错
    }
    int fd;
    fd = open("/dev/null",O_RDWR);
    dup2(fd,STDIN_FILENO);
    dup2(fd,STDOUT_FILENO);
    dup2(fd,STDERR_FILENO);
    return ;

}

int main(int argc, char* argv[]){
    daemonize();//切换到后台
    while(1){
        sleep(1);// unistd.h调用
    }
}








