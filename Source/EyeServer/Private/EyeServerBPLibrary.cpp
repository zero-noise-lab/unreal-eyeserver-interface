// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "EyeServerBPLibrary.h"
#include "EyeServer.h"
#include "EyeServerInterface.h"
#include "Windows/MinWindows.h"
#include <string>

UEyeServerBPLibrary::UEyeServerBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

FProcHandle UEyeServerBPLibrary::hProcess = FProcHandle(nullptr);


void UEyeServerBPLibrary::Connect()
{
	UE_LOG(LogTemp, Display, TEXT("EyeServer: connecting"));
	ensureMsgf(EyeServerInterface::Connect() == 0,
		TEXT("Could not connect to EyeServer"));
}

void UEyeServerBPLibrary::Disconnect()
{
	UE_LOG(LogTemp, Display, TEXT("EyeServer: disconnecting"));
	if (EyeServerInterface::Disconnect() != S_OK) {
		UE_LOG(LogTemp, Warning, TEXT("EyeServer: disconnect may have failed"));
	}
}

void UEyeServerBPLibrary::StartEyeLinkServerProcess()
{
	if (FPlatformProcess::IsApplicationRunning(TEXT("EyeLinkServer.exe"))) {
		UE_LOG(LogTemp, Warning, TEXT("EyeLinkServer.exe is already running. Stopping the process from Unreal may not work."));
		return;
	}

	UE_LOG(LogTemp, Display, TEXT("EyeServer: starting EyeLinkServer"));
	UEyeServerBPLibrary::hProcess = FPlatformProcess::CreateProc(TEXT("EyeLinkServer.exe"),
		TEXT(""), false, false, false, nullptr, 0, nullptr, nullptr);

	HANDLE hEvent = CreateEventA(nullptr, false, false, "EyeServerDone");
	DWORD result = WaitForSingleObject(hEvent, DWORD(10000));

}

void UEyeServerBPLibrary::StopEyeLinkServerProcess()
{
	UE_LOG(LogTemp, Display, TEXT("EyeServer: stopping EyeLinkServer process"));
	FPlatformProcess::TerminateProc(UEyeServerBPLibrary::hProcess);
	FPlatformProcess::WaitForProc(UEyeServerBPLibrary::hProcess);
	FPlatformProcess::CloseProc(UEyeServerBPLibrary::hProcess);
}

void UEyeServerBPLibrary::StartRecording()
{
	UE_LOG(LogTemp, Display, TEXT("EyeServer: starting recording without EDF"));
	ensureMsgf(EyeServerInterface::StartRecording() == 0,
		TEXT("EyeServer: could not start recording"));
}

int UEyeServerBPLibrary::CreateTarget(float x, float y, float r)
{
	UE_LOG(LogTemp, Display, TEXT("Creating EyeServer target at x=%.2f, y=%.2f, r=%.2f"), x, y, r);

	WORD key = 0;	
	ensureMsgf(EyeServerInterface::CreateTarget(x, y, r, &key) == S_OK,
		TEXT("EyeServer: could not create target on EyeServer"));
	UE_LOG(LogTemp, Display, TEXT("EyeServer: created target with key %d"), key);

	return key;
}

bool UEyeServerBPLibrary::IsEyeOnTarget(FString name)
{	
	name = TEXT("target");
	HANDLE hEvent = CreateEventA(NULL, FALSE, FALSE, (std::string(TCHAR_TO_UTF8(*name)) + "In" + "\0").c_str() );
	DWORD result = WaitForSingleObject(hEvent, 0);
	if (result == WAIT_OBJECT_0) {
		UE_LOG(LogTemp, Display, TEXT("EyeServer: eye is on target"));
		return true;
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("EyeServer: eye is NOT on target"));
		return false;
	}	
}

void UEyeServerBPLibrary::GetEyePosition(float& x, float& y)
{
	EyeServerInterface::GetEyePosition(x, y);
	UE_LOG(LogTemp, Display, TEXT("EyeServer: x=%.1f, y=%1.f"), x, y);

}
