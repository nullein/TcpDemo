#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <time.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>


#define BUFFSIZE 4096
#define PORT 8091
#define clinetQueue 10
using namespace std;

int main()
{
    //create fd
    int serverSock, clientSock;
    socklen_t len;
    int err;
    //sockaddr
    sockaddr_in serverAddr, clinetAddr;
    char buf[BUFFSIZE];
    //time_t
    time_t ticks;
    //create socket

    serverSock = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSock < 0) {
        cout << "create socket error !" << endl;
        exit(-1);
    }

    //serverAddr
    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    in_addr addr;
    inet_aton("127.0.0.1", &addr);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    //bind socket
    err = bind(serverSock, (sockaddr*)(&serverAddr), sizeof(serverAddr));
    if (err < 0) {
        cout << "bind error !" << endl;
        exit(-1);
    }

    cout << "listenning the port " << endl;
    //listen
    listen(serverSock, clinetQueue);

    while (1) {
        len = sizeof(clinetAddr);
        //accept
        clientSock = accept(serverSock, (sockaddr*)&clinetAddr, &len);
        
        cout << "connect from: " << inet_ntoa(clinetAddr.sin_addr) << " " << (clinetAddr.sin_port) << flush;
        
        ticks = time(NULL);
        sprintf(buf, "% .24s \r\n" , ctime(&ticks));
        write(clientSock, buf, strlen(buf));
        close(clientSock);
    
    }
    close(serverSock);
    
    exit(1);
}