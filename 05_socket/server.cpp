/*
 *程序名 server.cpp，此程序用于演示socket通信的服务端
 * 作者：C语言技术网(www.freecplus.net) 日期：20190525
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc,char *argv[])
{
    if (argc!=2)
    {
        printf("Using:./server port\nExample:./server 5005\n\n"); return -1;
    }

    // 第1步：创建服务端的socket。
    int listenfd;
    //ipv4 流socket
    if ( (listenfd = socket(AF_INET,SOCK_STREAM,0))==-1) { perror("socket"); return -1; }
    //设置SO_REUSEADDR选项
    int opt = 1; unsigned int len = sizeof(opt);
    setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&opt,len);
    // 第2步：把服务端用于通信的地址和端口绑定到socket上。
    struct sockaddr_in servaddr;    // 服务端地址信息的数据结构。
    memset(&servaddr,0,sizeof(servaddr));//结构体初始化为0
    servaddr.sin_family = AF_INET;  // 协议族，在socket编程中只能是AF_INET。
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);          // 任意ip地址。
    //servaddr.sin_addr.s_addr = inet_addr("192.168.190.134"); // 指定ip地址。
    servaddr.sin_port = htons(atoi(argv[1]));  // 指定通信端口。主机字节序转到网络字节序 atoi字符串转换为整型
    //端口范围
    //1024 1024以下系统保留 short是两个字节 16位 65535
    //
    //
    if (bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) != 0 )
    { perror("bind"); close(listenfd); return -1; }

    // 第3步：把socket设置为监听模式。
    //listen第二个参数是指目前监听到了几个
    if (listen(listenfd,5) != 0 ) { perror("listen"); close(listenfd); return -1; }
    //在这里等待
    // 第4步：接受客户端的连接。
    int  clientfd;                  // 客户端的socket。
    int  socklen=sizeof(struct sockaddr_in); // struct sockaddr_in的大小
    struct sockaddr_in clientaddr;  // 客户端的地址信息。
    sleep(20);
    while(1){
        //从已准备好的连接队列中获取一个请求，如果队列为空，accept函数将阻塞等待
        clientfd=accept(listenfd,(struct sockaddr *)&clientaddr,(socklen_t*)&socklen);
        printf("客户端（%s）已连接。\n",inet_ntoa(clientaddr.sin_addr));
    }
    // 第5步：与客户端通信，接收客户端发过来的报文后，回复ok。
    char buffer[1024];
    while (1)
    {
        int iret;
        memset(buffer,0,sizeof(buffer));
        if ( (iret=recv(clientfd,buffer,sizeof(buffer),0))<=0) // 接收客户端的请求报文。
        {
            printf("iret=%d\n",iret); break;   
        }
        printf("接收：%s\nz",buffer);

        strcpy(buffer,"ok");
        if ( (iret=send(clientfd,buffer,strlen(buffer),0))<=0) // 向客户端发送响应结果。
        { perror("send"); break; }
        printf("发送：%s\n",buffer);
    }

    // 第6步：关闭socket，释放资源。
    close(listenfd); close(clientfd); 
}

