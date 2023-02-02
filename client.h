// library used in the creation of connection to the server.
#include <iostream>
#include <stdio.h>
#include <winsock.h>
#include <time.h>
#include "hexaConvertor.h"
#include "checkValidity.h"
#include <cstdlib>
#include <thread>
#define PORT 5555
using namespace std;

// variable used in Socket creation
int nSocket;
WSADATA w;
sockaddr_in srv;
int clientPort;

void sending(bool exit) // function to send the message from string
{
    while (1)
    {
        string s;
        getline(cin, s);
        if (s == "close")
        {
            closesocket(nSocket);
            WSACleanup();
            cout << "!!!! CLIENT IS CLOSED !!!!" << endl;
            exit = true;
            return;
        }
        s = ASCIItoHEX(s);
        char sBuff[5000];
        for (int i = 0; i < s.length(); i++)
        {
            sBuff[i] = s[i];
        }
        sBuff[s.length()] = '\0';
        if (send(nSocket, sBuff, strlen(sBuff), 0) == SOCKET_ERROR)
        {
            cout << "!!!! CLIENT IS CLOSED !!!!" << endl;
            exit = true;
            return;
        }

        cout << "-----------------------------------------------------------------------" << endl;
        Sleep(200);
    }
}

void recieve(bool exit) // function to recieve the message from the server.
{
    while (1)
    {
        char buffer[1024];
        if (recv(nSocket, buffer, sizeof(buffer), 0) == SOCKET_ERROR)
        {
            closesocket(nSocket);
            WSACleanup();
            // cout << "!!!! SERVER IS CLOSED !!!!" << endl;
            exit = true;
            return;
        }

        string hex;
        int i = 0;
        while (buffer[i] != '\0')
        {
            hex.push_back(buffer[i]);
            i++;
        }
        hex = hexToASCII(hex);
        cout << "Recieved : " << hex << endl;
        cout << "-----------------------------------------------------------------------" << endl;
    }
}

int assignPortNo() // assign port to the clint
{

    int N = 10000;
    sockaddr_in clientAddr;
    clientAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    srand(time(0));
    clientAddr.sin_family = AF_INET;
    clientPort = (rand() % N);

    // cout << clientPort << endl;
    clientAddr.sin_port = htons(clientPort);
    memset(clientAddr.sin_zero, 0, sizeof(clientAddr.sin_zero));
    if (bind(nSocket, (SOCKADDR *)&clientAddr, sizeof(clientAddr)) == SOCKET_ERROR)
    {
        cout << "Socket binding is failed with error"
             << " " << WSAGetLastError() << endl;
        return -1;
    }
    return clientPort;
}

int setupClient()             // setup connection to the client
{ 
    int nRet = 0;
    nRet = WSAStartup(MAKEWORD(2, 2), &w);
    if (nRet < 0)
    {
        printf("\nCannot Initialize socket lib");
        return -1;
    }
    // Open a socket - listener
    nSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (nSocket < 0)
    {
        // errno is a system global variable which gets updated
        // with the last API call return value/result.
        printf("\nCannot Initialize listener socket:%d", errno);
        return -1;
    }
    int clientPort = assignPortNo();
    srv.sin_family = AF_INET;
    srv.sin_addr.s_addr = inet_addr("127.0.0.1");
    srv.sin_port = htons(PORT);
    memset(&(srv.sin_zero), 0, 8);
    nRet = connect(nSocket, (struct sockaddr *)&srv, sizeof(srv));
    if (nRet < 0)
    {
        printf("\nCannot connect to server:%d", errno);
        ;
        return -1;
    }
    return 0;
}
