
#include "EyeServerInterface.h"
#include <stdexcept> 
#include <string>

HANDLE EyeServerInterface::hPipe = INVALID_HANDLE_VALUE;

PROCESS_INFORMATION EyeServerInterface::processInformation;
STARTUPINFOA EyeServerInterface::startupInfo;

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

