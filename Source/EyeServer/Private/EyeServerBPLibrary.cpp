// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "EyeServerBPLibrary.h"
#include "EyeServer.h"
#include "EyeServerInterface.h"
#include "Windows/MinWindows.h"

UEyeServerBPLibrary::UEyeServerBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

FProcHandle UEyeServerBPLibrary::hProcess = FProcHandle(nullptr);


void UEyeServerBPLibrary::Connect()
{
	UE_LOG(LogTemp, Display, TEXT("Connect to EyeServer"));
	ensureMsgf(EyeServerInterface::Connect() == 0,
		TEXT("Could not connect to EyeServer"));
}

void UEyeServerBPLibrary::Disconnect()
{
	UE_LOG(LogTemp, Display, TEXT("Disconnect from EyeServer"));
	if (EyeServerInterface::Disconnect() != S_OK) {
		UE_LOG(LogTemp, Warning, TEXT("Disconnect from EyeServer may have failed"));
	}
}

void UEyeServerBPLibrary::StartEyeLinkServerProcess()
{
	if (FPlatformProcess::IsApplicationRunning(TEXT("EyeLinkServer.exe"))) {
		UE_LOG(LogTemp, Warning, TEXT("EyeLinkServer.exe is already running. Stopping the process from Unreal may not work."));
		return;
	}

	UE_LOG(LogTemp, Display, TEXT("Starting EyeLinkServer"));
	UEyeServerBPLibrary::hProcess = FPlatformProcess::CreateProc(TEXT("EyeLinkServer.exe"),
		TEXT(""), false, false, false, nullptr, 0, nullptr, nullptr);

	HANDLE hEvent = CreateEventA(nullptr, false, false, "EyeServerDone");
	DWORD result = WaitForSingleObject(hEvent, DWORD(10000));

}

void UEyeServerBPLibrary::StopEyeLinkServerProcess()
{
	UE_LOG(LogTemp, Display, TEXT("Stopping EyeServer"));
	FPlatformProcess::TerminateProc(UEyeServerBPLibrary::hProcess);
	FPlatformProcess::WaitForProc(UEyeServerBPLibrary::hProcess);
	FPlatformProcess::CloseProc(UEyeServerBPLibrary::hProcess);


}

void UEyeServerBPLibrary::StartRecording()
{
	UE_LOG(LogTemp, Display, TEXT("Starting EyeServer recording"));
	ensureMsgf(EyeServerInterface::StartRecording() == 0,
		TEXT("Could not start recording"));
}

int UEyeServerBPLibrary::CreateTarget(float x, float y, float r)
{
	WORD key = 0;
	EyeServerInterface::CreateTarget(x, y, r, &key);
	return key;
}
