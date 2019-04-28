#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

#define BUFFSIZE 4096
#define PORT 8091
#define HOST_ADDR "127.0.0.1"

using namespace std;

int main(int argc, int* argv[])
{
    int clientSock, n;
    int err;
    char recvBuff[BUFFSIZE];
    sockaddr_in serverAddr;

    clientSock = socket(PF_INET, SOCK_STREAM, 0);
    if (clientSock < 0) {
        cout << "clientSock create error " << endl;
        exit(-1);
    }

    bzero(&serverAddr, sizeof(serverAddr));
    inet_aton(HOST_ADDR, &serverAddr.sin_addr);
    serverAddr.sin_addr.s_addr = htonl(serverAddr.sin_addr.s_addr);
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_family = AF_INET;

    err = connect(clientSock, (sockaddr*)(&serverAddr), sizeof(serverAddr));
    if (err < 0) {
        cout << "connect error" << endl;
        exit(-1);
    }

    while ((n = read(clientSock, recvBuff, BUFFSIZE)) > 0) {
        recvBuff[n] = 0;
        fputs(recvBuff, stdout);
    }
    if (n < 0){
        cout << " read error " << endl;
        exit(-1);
    }
    return 0;
}