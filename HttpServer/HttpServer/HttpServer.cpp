// HttpServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "asio.hpp"
#include <signal.h>
#include "Server.h"

#ifdef __linux__
#include <stdio.h> //--список объявлений и используемых нами готовых библиотек Cи
#include <string.h> //--подробно о каждой библиотеке можно узнать в man
#include <sys/stat.h> //--например man stdio и.т.д
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <resolv.h>
#include <errno.h>
#endif

using namespace std;

int main(int argc, char* argv[])
{
    string ipAddr = "127.0.0.1";
    string port = "80";
    string siteDirectory = "./";

    for (int i = 0; i < argc; i++)
    {
        string parameter = argv[i];
        if (parameter == "-h" && i < argc - 1)
        {
            ipAddr = argv[i + 1];
        }

        if (parameter == "-p" && i < argc - 1)
        {
            port = argv[i + 1];
        }

        if (parameter == "-d" && i < argc - 1)
        {
            siteDirectory = argv[i + 1];
        }
    }

#ifdef __linux__
    pid_t parpid;
    if((parpid=fork())<0)
    {
        printf("\ncan't fork");
        exit(1);
    }
    else if (parpid!=0)
        exit(0);
    setsid();
#endif

    server httpServer(ipAddr, port, siteDirectory);

    httpServer.run();
	return 0;
}

