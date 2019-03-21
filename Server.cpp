#include <iostream>
#include <winsock2.h>
#include <string>
#include <cstring>
using namespace std;
struct Vec{
    int x,y,z;
};
struct Snd{
    uint16_t id_player;
    Vec pos;
    uint32_t id_karakter;
    char action[512];

};
int main(int argc, char *argv[])
{
    WSADATA wsa;
    SOCKET servSock, acceptSock;
    char savedBuffer[128] = "";
    char buffer[128] = "";

    unsigned int receivebyte,sended;
    struct sockaddr_in server, remoteAddr;
    cout<<"\nInitialize Winsock";
    if(WSAStartup(MAKEWORD(2,0),&wsa) == 0)
    {
        cout<<"\nInitialize Socket";
        memset(savedBuffer,0,strlen(savedBuffer));
        if((servSock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))!= INVALID_SOCKET)
        {
            server.sin_family = AF_INET;
            server.sin_addr.S_un.S_addr = INADDR_ANY;
            server.sin_port = htons(4500);
            cout<<"\ninitialize bind";
            if(bind(servSock,(sockaddr*)(&server),sizeof(server)) != SOCKET_ERROR)
            {
                cout<<"\nbind done";
                listen(servSock,2);
                int remoteAddrlen = sizeof(remoteAddr);

                cout<<"\nwaiting for connection";
                while((acceptSock = accept(servSock,(sockaddr*)(&remoteAddr),&(remoteAddrlen))) != INVALID_SOCKET)
                {
                    int i = 0;
                    cout<<"\nconnect from : "<<inet_ntoa(remoteAddr.sin_addr)<<":"<<htons(remoteAddr.sin_port);
                    char massage[] = "Connected";
                    if((sended = send(acceptSock,massage,strlen(massage),0)) == INVALID_SOCKET){
                        memset(massage,0,strlen(massage));
                    }
                    else{
                        cout<<"\nsend byte : "<<sended;
                    }
                    byte newbuffer[sizeof(Snd)];
                    receivebyte = recv(acceptSock,reinterpret_cast<char*>(newbuffer),sizeof(newbuffer),0);
                    Snd header;
                    memcpy(&header,newbuffer,sizeof(Snd));
                    cout<<"\nReceive Byte : "<<receivebyte;
                    cout<<"\nId User : "<<header.id_player
                    <<"\nId Karakter : "<<header.id_karakter
                    <<"\nPosition : X="<<header.pos.x<<",Y="<<header.pos.y<<",Z="<<header.pos.z
                    <<"\nAction : "<<header.action;
                    byte nbyte[sizeof(Snd)];
                    memcpy(nbyte,&header,sizeof(Snd));
                    sended = send(acceptSock,reinterpret_cast<char*>(nbyte),sizeof(nbyte),0);

                }
            }
        }
        else
            closesocket(servSock);
    }
    closesocket(servSock);
    WSACleanup();
    return 0;
}
