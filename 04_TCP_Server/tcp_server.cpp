#include<iostream>
#include<cstdlib>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#define MESSAGE_LEN 1024
#define PORT 8111
int main(int argc,char* argv[]){
    int ret = -1;
    int socket_fd,accept_fd;
    int on = 1;
    int backlog = 10;
    struct sockaddr_in localaddr,remoteaddr;

    char in_buff[MESSAGE_LEN] = {0,};
//    int socket(int domain, int type, int protocol);   socket()函数的原型，这个函数j
    socket_fd = socket(AF_INET,SOCK_STREAM,0); //创建socket  FP_INET是 IPv4互联网协议族 SOCK_STREAM是面向连接的套接字  第三个参数传0
    if(socket_fd == -1){    //返回文件描述符 失败时返回-1
        std::cout<<"Failed to create socket!"<<std::endl;
        exit(-1);
    }
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
        socklen_t addr_len = sizeof(struct sockaddr);
        accept_fd  = accept(socket_fd,
                (struct sockaddr *) &remoteaddr,
                &addr_len);
        for(;;){
            ret = recv(accept_fd,(void *)in_buff,MESSAGE_LEN,0);
            if(ret == 0){ 
                break;
            }
            std::cout<<"server recv:"<<in_buff;
            send(accept_fd,(void *)in_buff,MESSAGE_LEN,0);
        }
        close(accept_fd);
    }
    close(socket_fd);
    return 0;
}
