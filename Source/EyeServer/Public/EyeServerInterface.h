#pragma once

#include "Windows/MinWindows.h"
#include <vector>
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
	static DWORD iRecStart();
	static DWORD StopEyeServerProcess();	
	static DWORD StartRecording();
	static DWORD StartRecording(std::string filename);
	static DWORD StopRecording();
	static DWORD StopRecording(std::string filename);
	static DWORD CreateTarget(float x, float y, float r, unsigned short *pKey, std::string name);
	static DWORD ReadAcknowledgement(unsigned short *pKey);
	static DWORD RemoveTarget(unsigned short pKey);
	static DWORD RemoveAllTargets();
	static DWORD ResizeTarget(unsigned short pKey, float r);
	static DWORD GetEyePosition(float& x, float& y);
	static DWORD RescaleDisplay();
	static DWORD SendiRecEventmarker(signed int markercode);
	static DWORD AcceptiRecCalibrationPoint();

private:
	static HANDLE hPipe;
	static PROCESS_INFORMATION processInformation;
	static STARTUPINFOA startupInfo;	
	static HANDLE hEyePosMap;
	static LPVOID pEyePosMem;
	static bool recordingStarted;
	static std::vector < unsigned short > targetKeys;
};

