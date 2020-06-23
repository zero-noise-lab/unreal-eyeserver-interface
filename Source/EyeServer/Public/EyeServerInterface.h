#pragma once

#include "Windows/MinWindows.h"
#define BUFFERSIZE 256

union COMMANDBUFFER {
	unsigned char command[BUFFERSIZE];
	struct {
		BYTE type;
		unsigned char body[BUFFERSIZE - 1];
	};
};
class EyeServerInterface
{
public:
	static DWORD Connect();
	static DWORD Disconnect();
	static DWORD StartEyeLinkServerProcess();
	static DWORD StopEyeLinkServerProcess();

private:
	static HANDLE hPipe;
	static PROCESS_INFORMATION processInformation;
	static STARTUPINFOA startupInfo;	
};

