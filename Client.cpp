#include <iostream>
#include <winsock2.h>
#include <string>
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
int main()
{
    struct Snd headr;
    WSADATA wsa;
    SOCKET clientsock;
    char buffer[512];
    char massage[128];
    unsigned int connected, received, sendByte;
    sockaddr_in client;
    if(WSAStartup(MAKEWORD(2,0),&wsa) == 0)
    {

        cout<<"\nInisialize Winsock Succeed";
        if((clientsock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) != INVALID_SOCKET)
        {
            cout<<"\nInisialize Socket Succeed";
            client.sin_family = AF_INET;
            client.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
            client.sin_port = htons(4500);
            int addrlen = sizeof(client);
            if((connected = connect(clientsock,(sockaddr*)&client,addrlen))!= SOCKET_ERROR){
                memset(massage,0,sizeof(massage));
                received = recv(clientsock,massage,sizeof(massage),0);
                if(received == SOCKET_ERROR){
                    cout<<"\nFailed received"<<WSAGetLastError();
                }
                else{

                    cout<<"\nByte Received : "<<received;
                    cout<<"\n"<<massage<<"\n";
                }

                headr.id_karakter = 42331;
                headr.id_player = 2231;
                headr.pos.x = 10;
                headr.pos.y = 30;
                headr.pos.z = 42;
                strcpy(headr.action,"Attack");
                char data[sizeof(Snd)];
                memcpy(data,&headr,sizeof(Snd));
                sendByte = send(clientsock,data,sizeof(Snd),0);
                cout<<"\nSend Byte = "<<sendByte;
            }
        }else{
            closesocket(clientsock);
        }
    }
    closesocket(clientsock);
    WSACleanup();
    system("pause");
}
