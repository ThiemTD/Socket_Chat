// Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Client.h"
#include "afxsock.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: change error code to suit your needs
			_tprintf(_T("Fatal Error: MFC initialization failed\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: code your application's behavior here.
			//============================================

			//Khai bao su dung socket trong WINDOW
			AfxSocketInit(NULL);

			//Socket Client

			CSocket client;

			// Khoi tao socket
			client.Create(); // Khong can khoi tao port

			//Ket noi toi server
			client.Connect(_T("10.1.1.11Ưha"), 6628);

			//Start chat
			char msg[100];
			int len = 0;
			while (true)
			{
				//Client chat truoc
				cout << "\nClient says: ";
				gets(msg);
				len = strlen(msg);
				//Gui thong tin toi Server

				client.Send(&len, sizeof(int), 0);
				client.Send(msg, len, 0);

				//Nhan thong diep tu server
				client.Receive(&len, sizeof(int), 0);
				char* temp = new char[len + 1];
				client.Receive(temp, len, 0);
				temp[len] = 0;
				// Hien thi thong diep
				cout << "Server says: " << temp;

				delete temp;
			}

			client.Close();
			//============================================
		}
	}
	else
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: GetModuleHandle failed\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
