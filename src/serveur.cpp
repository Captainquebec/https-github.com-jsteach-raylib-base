#define DEFAULT_PORT "6767"
#include "entrypoint.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include "stdio.h"
#ifdef _WIN32
#elif __linux__
#endif
using namespace std;

struct addrinfo *result = NULL, *ptr = NULL, hints;
SOCKET ListenSocket = INVALID_SOCKET;

int init_serveur(void){
#ifdef _WIN32
WSADATA wsaData;

int iResult;

iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
if (iResult != 0) {
    printf("WSAStartup failed: %d\n", iResult);
    return 1;
}
#endif

ZeroMemory(&hints, sizeof (hints));
hints.ai_family = AF_INET; //ipv4
hints.ai_socktype = SOCK_STREAM;
hints.ai_protocol = IPPROTO_TCP; //tpc
hints.ai_flags = AI_PASSIVE;

// Resolve the local address and port to be used by the server
 INT iResult = getaddrinfo("127.0.1", DEFAULT_PORT, &hints, &result);
if (iResult != 0) {
    printf("getaddrinfo failed: %d\n", iResult);
    WSACleanup();
    return -1;
        }
   
ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
if (ListenSocket == INVALID_SOCKET) {
    printf("Error at socket(): %ld\n", WSAGetLastError());
    freeaddrinfo(result);
    WSACleanup();
    return -1;
    }

    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        
        closesocket(ListenSocket);
        WSACleanup();
        return -1;
    }
    freeaddrinfo(result);

    if ( listen( ListenSocket, SOMAXCONN ) == SOCKET_ERROR ) {
    printf( "Listen failed with error: %ld\n", WSAGetLastError() );
    closesocket(ListenSocket);
    WSACleanup();
    return -1;
}

}

#define DEFAULT_BUFLEN 512 
char recvbuf[DEFAULT_BUFLEN] = {'S' , 'T' , 'A' , 'R' , 'T' , '/0'};
int iResult, iSendResult;

void raylib_start(void){
 if( init_serveur() < 0)
   {
    exit(1);
   }
   SOCKET ClientSocket;
   ClientSocket = INVALID_SOCKET;


    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
    printf("accept failed: %d\n", WSAGetLastError());
    closesocket(ListenSocket);
    WSACleanup();
    exit(1);
    }
    int iResult =1;
    While (iResult > 0) {
        if (iResult > 0){}
        printf("Bytes received:%d\n", iResult);

        iSendResult = send(ClientSocket, recvbuf, iResult, 0);
        if (iSendResult == SOCKET_ERROR) {
            printf("send failed: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            return 1;
        }
        printf("Bytes sent: %d\n", iSendResult);
                            } else if (iResult == 0)
        printf("Connection closing...\n");
        else {
        printf("recv failed: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        exit(1);
                    }
                     iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
}