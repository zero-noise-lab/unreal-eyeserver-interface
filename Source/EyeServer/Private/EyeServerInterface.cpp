
#include "EyeServerInterface.h"
#include <stdexcept> 
#include <string>
#include <array>

HANDLE EyeServerInterface::hPipe = INVALID_HANDLE_VALUE;

PROCESS_INFORMATION EyeServerInterface::processInformation;
STARTUPINFOA EyeServerInterface::startupInfo;

HANDLE EyeServerInterface::hEyePosMap = INVALID_HANDLE_VALUE;
LPVOID EyeServerInterface::pEyePosMem = nullptr;

bool EyeServerInterface::recordingStarted = false;

DWORD EyeServerInterface::Connect()
{
	// No need to connect again if already connected
	if (EyeServerInterface::hPipe != INVALID_HANDLE_VALUE) {		
		return S_OK;
	}

	// Connect to pipe
	EyeServerInterface::hPipe = CreateFileA("\\\\.\\pipe\\EyeServerPipe",
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	if (EyeServerInterface::hPipe == INVALID_HANDLE_VALUE) 		 
	{
		return GetLastError();
	}
	
	// Open shared memory
	EyeServerInterface::hEyePosMap = OpenFileMappingA(FILE_MAP_READ, false, "EyePosition");	
	if (EyeServerInterface::hEyePosMap == NULL)
	{
		return GetLastError();
	}

	EyeServerInterface::pEyePosMem = MapViewOfFile(EyeServerInterface::hEyePosMap, FILE_MAP_READ, NULL, NULL, NULL);
	if (EyeServerInterface::pEyePosMem == NULL)
	{
		return GetLastError();
	}

	return S_OK;

}

DWORD EyeServerInterface::Disconnect()
{
	// Close pipe
	bool disconnectSuccess = DisconnectNamedPipe(hPipe);
	bool closeSuccess = CloseHandle(hPipe);
	EyeServerInterface::hPipe = INVALID_HANDLE_VALUE;

	if (disconnectSuccess & closeSuccess) {
		return S_OK;
	}
	else
	{
		return GetLastError();
	}
	
}



DWORD EyeServerInterface::StartEyeLinkServerProcess()
{
	ZeroMemory(&EyeServerInterface::startupInfo, sizeof(EyeServerInterface::startupInfo));
	EyeServerInterface::startupInfo.cb = sizeof(EyeServerInterface::startupInfo);
	ZeroMemory(&EyeServerInterface::processInformation, sizeof(EyeServerInterface::processInformation));

	// Start the child process. 
	if (!CreateProcessA("EyeLinkServer.exe",   // Module name
		NULL,           // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&EyeServerInterface::startupInfo,            // Pointer to STARTUPINFO structure
		&EyeServerInterface::processInformation)           // Pointer to PROCESS_INFORMATION structure
		)
	{
		return GetLastError();
	}
	else {
		return S_OK;
	}
}

DWORD EyeServerInterface::StopEyeLinkServerProcess()
{
	TerminateProcess(EyeServerInterface::processInformation.hProcess, 1);
	CloseHandle(EyeServerInterface::processInformation.hProcess);
	CloseHandle(EyeServerInterface::processInformation.hThread);
	return S_OK;
}


DWORD EyeServerInterface::StartRecording()
{



	#pragma pack(push, 1)
	static struct {
		unsigned short key = 0;
		BYTE cmd[2] = { 0, 2 };
	} msg;
	#pragma pack(pop)	
	
	DWORD nBytesWritten = 0;
	bool success = WriteFile(EyeServerInterface::hPipe, &msg.key, 4, &nBytesWritten, NULL);
	if ((!success) & (nBytesWritten == 4))
	{
		return GetLastError();
	}

	EyeServerInterface::recordingStarted = true;
	return S_OK;
}

DWORD EyeServerInterface::StartRecording(std::string filename)
{
	if (EyeServerInterface::recordingStarted) {
		return S_OK;
	}

	//[00 0 2 filename] start recording

	#pragma pack(push, 1)
	static struct {
		unsigned short key = 0;
		BYTE cmd[2] = { 0, 2 };
		std::string filename;
	} msg;
	#pragma pack(pop)	

	msg.filename = filename;

	DWORD nBytesWritten = 0;
	bool success = WriteFile(EyeServerInterface::hPipe, &msg.key, sizeof(msg), &nBytesWritten, NULL);
	if ((!success) & (nBytesWritten == sizeof(msg)))
	{
		return GetLastError();
	}

	EyeServerInterface::recordingStarted = true;
	return S_OK;
}

DWORD EyeServerInterface::StopRecording()
{
	// [00 0 0]
	if (!EyeServerInterface::recordingStarted) {
		return S_OK;
	}
	#pragma pack(push, 1)
	static struct {
		unsigned short key = 0;
		BYTE cmd[2] = { 0, 0 };
	} msg;
	#pragma pack(pop)
	DWORD nBytesWritten = 0;
	bool success = WriteFile(EyeServerInterface::hPipe, &msg.key, sizeof(msg), &nBytesWritten, NULL);
	if ((!success) & (nBytesWritten == sizeof(msg)))
	{
		return GetLastError();
	}

	EyeServerInterface::recordingStarted = false;

	return S_OK;
}

DWORD EyeServerInterface::StopRecording(std::string filename)
{
	// [00 0 0 filename]
	if (!EyeServerInterface::recordingStarted) {
		return S_OK;
	}
	#pragma pack(push, 1)
	static struct {
		unsigned short key = 0;
		BYTE cmd[2] = { 0, 0 };
		std::string filename;
	} msg;
	#pragma pack(pop)
	msg.filename = filename;

	DWORD nBytesWritten = 0;
	bool success = WriteFile(EyeServerInterface::hPipe, &msg.key, sizeof(msg), &nBytesWritten, NULL);
	if ((!success) & (nBytesWritten == sizeof(msg)))
	{
		return GetLastError();
	}

	EyeServerInterface::recordingStarted = false;

	HANDLE hEvent = CreateEventA(nullptr, false, false, "EyeServerDone");
	DWORD result = WaitForSingleObject(hEvent, DWORD(180000));

	return S_OK;
}

DWORD EyeServerInterface::CreateTarget(float x, float y, float r, WORD * pKey, std::string name)
{
	#pragma pack(push, 1)
	static struct {
		unsigned short key = 0;
		BYTE cmd = 1;
		float x = 0.;
		float y = 0.;
		float r = 100.;
		std::string name;
	} targetMsg;
	#pragma pack(pop)	

	targetMsg.x = x;
	targetMsg.y = y;
	targetMsg.r = r;
	targetMsg.name = name;
	
	DWORD nBytesWritten = 0;
	bool success = WriteFile(EyeServerInterface::hPipe, &targetMsg.key, sizeof(targetMsg), &nBytesWritten, NULL);
	if ((!success))
	{
		return GetLastError();
	}

	return EyeServerInterface::ReadAcknowledgement(pKey);
		
}


DWORD EyeServerInterface::ReadAcknowledgement(WORD * pKey) 
{
	DWORD nBytesRead = 0;
	bool success = ReadFile(EyeServerInterface::hPipe, pKey, 2, &nBytesRead, NULL);
	if ((success) & (nBytesRead == 2))
	{
		return S_OK;
	}
	else {
		return GetLastError();
	}
	
}

DWORD EyeServerInterface::GetEyePosition(float& x, float& y)
{
	std::array<float, 2> pos = *(std::array<float, 2>*) EyeServerInterface::pEyePosMem;
	x = pos[0];
	y = pos[1];

	return S_OK;
}





