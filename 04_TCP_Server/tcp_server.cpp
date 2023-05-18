#include<iostream>
#include<cstdlib>
#include<unistd.h>
#include<fcntl.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#define MESSAGE_LEN 1024
#define PORT 8111
#define FD_SIZE 1024
int main(int argc,char* argv[]){
    int ret = -1;
    int socket_fd,accept_fd;
    int on = 1;
    pid_t pid;
    int backlog = 10;
    struct sockaddr_in localaddr,remoteaddr;
    int flags;
    int events = 0;
    int max_fd = -1;
    int curpos = -1;
    fd_set fd_sets;
    int accept_fds[FD_SIZE]={-1,};


    char in_buff[MESSAGE_LEN] = {0,};
    //    int socket(int domain, int type, int protocol);   socket()函数的原型，这个函数j
    socket_fd = socket(AF_INET,SOCK_STREAM,0); //创建socket  FP_INET是 IPv4互联网协议族 SOCK_STREAM是面向连接的套接字  第三个参数传0
    if(socket_fd == -1){    //返回文件描述符 失败时返回-1
        std::cout<<"Failed to create socket!"<<std::endl;
        exit(-1);
    }
    //设置为非阻塞
    flags = fcntl(socket_fd,F_GETFL,0);
    fcntl(socket_fd,F_SETFL,flags | O_NONBLOCK);
    max_fd = socket_fd;

    //设置sockopt
    ret =  setsockopt(socket_fd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));//文件描述符 套接字层次 主动关闭的会发起timewait 使用re_useaddr不用等待 
    if(ret == -1){
        std::cout<<"Failed to set socket options!"<<std::endl;
    }
    localaddr.sin_family = AF_INET;
    localaddr.sin_port = PORT;
    localaddr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(localaddr.sin_zero),8);
    ret = bind(socket_fd,(struct sockaddr *)&localaddr,sizeof(struct sockaddr));
    if(ret == -1){
        std::cout<<"Failed to bind addr!"<<std::endl;
        exit(-1);
    }
    ret = listen(socket_fd,backlog);
    if(ret == -1){
        std::cout<<"Failed to listen socket!"<<std::endl;
        exit(-1);
    }
    while(1){

        FD_ZERO(&fd_sets);
        FD_SET(socket_fd,&fd_sets);
        for(int i=0;i<FD_SIZE;i++){
            if(accept_fds[i] != -1){
                if(accept_fds[i] > max_fd){
                    max_fd = accept_fds[i];
                }
                FD_SET(accept_fds[i],&fd_sets); //加入这个进程
            }
        }

        events = select(max_fd+1,&fd_sets,NULL,NULL,NULL);
        if(events < 0) {
            std::cout<<"Failed to use select!"<<std::endl;
            break;
        }else if(events == 0){
            std::cout<<"timeout...!"<<std::endl;
            continue;
        }else if(events){
            if(FD_ISSET(socket_fd,&fd_sets)){
                for(int i=0;i<FD_SIZE;i++){
                    if(accept_fds[i] == -1){
                        curpos = i;
                        break;
                    }
                }

                socklen_t addr_len = sizeof(struct sockaddr);
                accept_fd  = accept(socket_fd,
                        (struct sockaddr *) &remoteaddr,
                        &addr_len);
                flags = fcntl(accept_fd,F_GETFL,0);
                fcntl(accept_fd,F_SETFL,flags | O_NONBLOCK);
                accept_fds[curpos] = accept_fd;
            }
            for(int i=0;i<FD_SIZE;i++){
                if(accept_fds[i] != -1 && FD_ISSET(accept_fds[i],&fd_sets)){
                    memset(in_buff,0,MESSAGE_LEN);
                    ret = recv(accept_fds[i],(void *)in_buff,MESSAGE_LEN,0);
                    if(ret == 0){
                        close(accept_fds[i]);
                        break;
                    }
                    std::cout<<"server recv:"<<in_buff;
                    send(accept_fds[i],(void *)in_buff,MESSAGE_LEN,0);
                }
            }

        }
    }
    close(socket_fd); //侦听的
    return 0;
}
