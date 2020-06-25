
#include "EyeServerInterface.h"
#include <stdexcept> 
#include <string>
#include <array>

HANDLE EyeServerInterface::hPipe = INVALID_HANDLE_VALUE;

PROCESS_INFORMATION EyeServerInterface::processInformation;
STARTUPINFOA EyeServerInterface::startupInfo;

HANDLE EyeServerInterface::hEyePosMap = INVALID_HANDLE_VALUE;
LPVOID EyeServerInterface::pEyePosMem = nullptr;

DWORD EyeServerInterface::Connect()
{
	if (EyeServerInterface::hPipe != INVALID_HANDLE_VALUE) {		
		return S_OK;
	}
	EyeServerInterface::hPipe = CreateFileA("\\\\.\\pipe\\EyeServerPipe",
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);

	if (EyeServerInterface::hPipe != INVALID_HANDLE_VALUE) 		 
	{
		return S_OK;
	}
	else {
		return GetLastError();
	}

	// FIXME: add error checking
	EyeServerInterface::hEyePosMap = OpenFileMappingA(FILE_MAP_READ, false, "EyePosition");	
	EyeServerInterface::pEyePosMem = MapViewOfFile(EyeServerInterface::hEyePosMap, FILE_MAP_READ, NULL, NULL, NULL);



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

	return S_OK;
}

DWORD EyeServerInterface::CreateTarget(float x, float y, float r, WORD * pKey)
{
	#pragma pack(push, 1)
	static struct {
		unsigned short key = 0;
		float x = 0.;
		float y = 0.;
		float r = 0.;
		std::string name;
	} targetMsg;
	#pragma pack(pop)	

	targetMsg.x = x;
	targetMsg.y = y;
	targetMsg.r = r;
	targetMsg.name = "target";
	
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

auto EyeServerInterface::GetEyePosition()
{
	return *(std::array<float, 2>*) EyeServerInterface::pEyePosMem;			
}





