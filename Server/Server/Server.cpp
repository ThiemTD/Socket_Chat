// Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Server.h"
#include "afxsock.h"
#include <tchar.h>
#include <windows.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;
	wchar_t m_IP[16];
	GetPrivateProfileString(L"Settings", L"IP", L"", m_IP, sizeof(m_IP), L".\\ServerConfig.ini");
	int m_Port = GetPrivateProfileInt(L"Settings", L"Port", 0, L".\\ServerConfig.ini");
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

			CSocket server;
			CSocket client;

			//Khoi tao socket voi port
			server.Create(m_Port);

			//Nghe ket noi tu client
			server.Listen();
			
			cout << "Waiting for client" << endl;

			//Chap nhan ket noi tu client

			if (server.Accept(client))
			{
				cout << "Client is connected." << endl;
			}

			char msg[100];
			int len = 0;
			//Bat dau chat 
			while (true)
			{
				//Nhan thong diep tu client
				client.Receive(&len, sizeof(int), 0);

				char* temp = new char[len + 1];
				client.Receive(temp, len, 0);
				temp[len] = '\0';

				//In thong diep
				cout << "\nClient says: " << temp << endl;
				delete temp;

				//Gui thong diep cho client
				cout << "Server says: ";
				gets(msg);
				len = strlen(msg);

				//Gui di
				client.Send(&len, sizeof(int), 0);
				client.Send(msg, len, 0);
			}

			client.Close();
			server.Close();
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
