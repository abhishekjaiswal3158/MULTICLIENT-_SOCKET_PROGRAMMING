#include "client.h"

int main()
{

    int res = setupClient(); // client setup function like creation,binding,connect.
    if (res == -1)
    {             // setupClient() function return -1 if client can not connect to the server.
        return 0; // exit
    }
    cout << "    ////////////////////////////////////////////////////" << endl
         << "    //   WELCOME TO CLIENT RUNNING ON PORT NO:" << clientPort << "    //" << endl
         << "    ////////////////////////////////////////////////////" << endl;
    cout << endl
         << "-----------------------------------------------------------------------" << endl;
    bool exit = false;
    cout<<"DESTINATION PORT USE #----# AND SOURCE PORT USE @----@."<<endl;
    cout<<"--------------------------------------------------------------------------"<<endl;
    std::thread thread1(sending, exit); // creation of thread for sending to the server
    std::thread thread2(recieve, exit); // creation of thread for recieving from the server

    if (exit == true)
    {
        return 0;
    }
    Sleep(2000000);
    thread1.join(); // blocks the calling thread1
    thread2.join(); // blocks the calling thread2
    return 0;
}