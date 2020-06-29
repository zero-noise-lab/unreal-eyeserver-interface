#pragma once

#include "Windows/MinWindows.h"
#include <string>
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
	static DWORD StartRecording();
	static DWORD CreateTarget(float x, float y, float r, WORD * key, std::string name);
	static DWORD ReadAcknowledgement(WORD * pKey);
	static DWORD GetEyePosition(float& x, float& y);

private:
	static HANDLE hPipe;
	static PROCESS_INFORMATION processInformation;
	static STARTUPINFOA startupInfo;	
	static HANDLE hEyePosMap;
	static LPVOID pEyePosMem;
	static bool recordingStarted;
};

