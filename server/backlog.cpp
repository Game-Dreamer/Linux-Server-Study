#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <string.h>
#include "./socket.h"

using namespace std;

static bool stop = false;

static void handle_term(int sig)
{
    stop = true;
}

int main(int argc,char* argv[])
{
    signal(SIGTERM,handle_term);
    if(argc <= 3)
    {
        cout<<"usage: "<<basename(argv[0])<<"ip_address port backlog"<<endl;
        return 1;
    }
    Socket socket(IPv4,STREAM);
    
    const char* ip = argv[1];
    int port = atoi(argv[2]);
    int backlog = atoi(argv[3]);
    socket.bind(ip,port);
    socket.listen(backlog);
    
    
    //int sock = socket(PF_INET,SOCK_STREAM,0);
    //assert(sock >= 3);
    
    /*创建一个IPv4 socket地址*/
    //struct sockaddr_in address;
    //bzero(&address,sizeof(address));
    //address.sin_family = AF_INET;
    //inet_pton(AF_INET,ip,&address.sin_addr);
    //address.sin_port = htons(port);

    //int ret = bind(sock,(struct sockaddr*)&address,sizeof(address));
    //assert(ret != -1);
    //ret = listen(sock,backlog);
    //assert(ret != -1);
    while(!stop)
    {
        cout<<"waiting for connection..."<<endl;
        sleep(1);
    }
    socket.~Socket();
    //close(sock);
    return 0;
}