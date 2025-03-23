#pragma once
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

//PF_INET表示IPv4协议，PF_INET6表示IPv6协议
//对PF_INET和PF_INET6的定义在sys/socket.h中
//使用枚举类型进行更名封装
enum Domain
{
    IPv4 = PF_INET,
    IPv6 = PF_INET6,
};

//STREAM表示流式传输，使用TCP协议，DGRAM表示数据报传输，使用UDP协议
//对SOCK_STREAM月和SOCK_DGRAM的定义在sys/socket.h中
//使用枚举类型进行更名封装
enum Type
{
    STREAM = SOCK_STREAM,
    DGRAM =  SOCK_DGRAM
};

class Socket
{
    public:
        //使用协议族和套接字类型进行初始化，目前不支持PF_UNIX协议族
        Socket(Domain domain, Type type);
        
        //在析构函数中关闭套接字
        ~Socket();
        
        void close();
        //使用bind函数进行绑定，对Linux原生bind函数进行封装，返回值仍为原生返回值含义
        int bind(std::string ip, int port);
        
        //对原生listen函数进行封装，返回值仍为原生返回值含义，参数为能够接受的最大接受数
        int listen(int backlog);
        
        //对原生accept函数进行封装，返回值仍为原生返回值含义
        //参数为客户端的地址和长度，为返回值参数，可为nullptr，表示不关心客户端地址，默认nullptr
        int accept(struct sockaddr_in* client,socklen_t* len);
        
        //对原生connect函数进行封装，返回值为原生返回值含义
        int connect(std::string ip, int port);
    private:
        int sockfd;
        Type type;
        Domain domain;
};