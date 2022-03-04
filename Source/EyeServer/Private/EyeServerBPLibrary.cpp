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

void UEyeServerBPLibrary::StartiRecServerProcess()
{
	if (FPlatformProcess::IsApplicationRunning(TEXT("iRecServer.exe"))) {
		UE_LOG(LogTemp, Warning, TEXT("iRecServer.exe is already running. Stopping the process from Unreal may not work."));
		return;
	}

	UE_LOG(LogTemp, Display, TEXT("EyeServer: starting iRecServer"));
	UEyeServerBPLibrary::hProcess = FPlatformProcess::CreateProc(TEXT("iRecServer.exe"),
		TEXT(""), false, false, false, nullptr, 0, nullptr, nullptr);

	HANDLE hEvent = CreateEventA(nullptr, false, false, "EyeServerDone");
	DWORD result = WaitForSingleObject(hEvent, DWORD(10000));

	ensureMsgf(EyeServerInterface::iRecStart() == 0,
		TEXT("EyeServer: could not start iRec ports (TCP or UDP)"));

	UE_LOG(LogTemp, Display, TEXT("EyeServer: StartiRecServerProcess done"));

}

void UEyeServerBPLibrary::StopEyeServerProcess()
{
	UE_LOG(LogTemp, Display, TEXT("EyeServer: stopping running EyeServer process"));
	FPlatformProcess::TerminateProc(UEyeServerBPLibrary::hProcess);
	FPlatformProcess::WaitForProc(UEyeServerBPLibrary::hProcess);
	FPlatformProcess::CloseProc(UEyeServerBPLibrary::hProcess);
}

bool UEyeServerBPLibrary::isEyeServerRunning()
{
	return FPlatformProcess::IsProcRunning(UEyeServerBPLibrary::hProcess);
}

void UEyeServerBPLibrary::StartRecording()
{
	UE_LOG(LogTemp, Display, TEXT("EyeServer: starting recording without EDF"));
	ensureMsgf(EyeServerInterface::StartRecording() == 0,
		TEXT("EyeServer: could not start recording"));
}

void UEyeServerBPLibrary::StartRecordingWithFile(FString filename)
{
	UE_LOG(LogTemp, Display, TEXT("EyeServer: starting recording with filename %s"), *filename);
	ensureMsgf(EyeServerInterface::StartRecording(std::string(TCHAR_TO_UTF8(*filename))) == 0,
		TEXT("EyeServer: could not start recording"));
}

void UEyeServerBPLibrary::StopRecording()
{
	UE_LOG(LogTemp, Display, TEXT("EyeServer: stopping recording without EDF"));
	ensureMsgf(EyeServerInterface::StopRecording() == 0,
		TEXT("EyeServer: could not stop recording"));
}

void UEyeServerBPLibrary::StopRecordingWithFile(FString filename)
{
	UE_LOG(LogTemp, Display, TEXT("EyeServer: stopping recording and copying to file %s"), *filename);
	ensureMsgf(EyeServerInterface::StopRecording(std::string(TCHAR_TO_UTF8(*filename))) == 0,
		TEXT("EyeServer: could not stop recording"));

}

int UEyeServerBPLibrary::CreateTarget(float x, float y, float r, FString name)
{
	UE_LOG(LogTemp, Display, TEXT("Creating EyeServer target at x=%.2f, y=%.2f, r=%.2f"), x, y, r);

	unsigned short key = 0;	
	ensureMsgf(EyeServerInterface::CreateTarget(x, y, r, &key, std::string(TCHAR_TO_UTF8(*name))) == S_OK,
		TEXT("EyeServer: could not create target on EyeServer"));
	UE_LOG(LogTemp, Display, TEXT("EyeServer: created target %s with key %d"), *name, key);

	return key;
}

void UEyeServerBPLibrary::RemoveAllTargets()
{
	ensureMsgf(EyeServerInterface::RemoveAllTargets() == S_OK,
		TEXT("EyeServer: could not remove all targets on EyeServer"));
	UE_LOG(LogTemp, Display, TEXT("EyeServer: removed all targets"));

}

void UEyeServerBPLibrary::RemoveTarget(int key)
{
	UE_LOG(LogTemp, Display, TEXT("Removing EyeServer target key %d"), key);

	ensureMsgf(EyeServerInterface::RemoveTarget(unsigned short (key)) == S_OK,
		TEXT("EyeServer: could not create target on EyeServer"));
	UE_LOG(LogTemp, Display, TEXT("EyeServer: removed target with key %d"), key);

}

void UEyeServerBPLibrary::ResizeTarget(int key, float r)
{
	UE_LOG(LogTemp, Display, TEXT("Resizing EyeServer target key %d to %.2f"), key, r);

	ensureMsgf(EyeServerInterface::ResizeTarget(unsigned short(key), r) == S_OK,
		TEXT("EyeServer: could not resize target on EyeServer"));
	UE_LOG(LogTemp, Display, TEXT("EyeServer: resized target with key %d"), key);

}

bool UEyeServerBPLibrary::IsEyeOnTarget(FString name)
{	
	HANDLE hEvent = CreateEventA(NULL, FALSE, FALSE, (std::string(TCHAR_TO_UTF8(*name)) + "In" + "\0").c_str() );
	DWORD result = WaitForSingleObject(hEvent, 0);
	if (result == WAIT_OBJECT_0) {
		UE_LOG(LogTemp, Display, TEXT("EyeServer: eye is on target %s"), *name);
		return true;
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("EyeServer: eye is NOT on target %s"), *name);
		return false;
	}	
}

void UEyeServerBPLibrary::GetEyePosition(float& x, float& y)
{
	EyeServerInterface::GetEyePosition(x, y);
	UE_LOG(LogTemp, Display, TEXT("EyeServer: x=%.1f, y=%1.f"), x, y);

}

void UEyeServerBPLibrary::RescaleDisplay()
{
	UE_LOG(LogTemp, Display, TEXT("EyeServer: Rescale display"));
	ensureMsgf(EyeServerInterface::RescaleDisplay() == 0,
		TEXT("EyeServer: could not rescale display "));
}

void UEyeServerBPLibrary::SendiRecEventmarker(int code)
{
	UE_LOG(LogTemp, Display, TEXT("EyeServer: Sent iRec UDP %d"), code);
	// ensureAlwaysMsgf(EyeServerInterface::SendiRecEventmarker(signed int(code)) == S_OK,
	// 	TEXT("Could not send iRec eventmarker"));
	DWORD result = EyeServerInterface::SendiRecEventmarker(signed int(code));
	if (result == S_OK) {
		UE_LOG(LogTemp, Display, TEXT("EyeServer: eventmarker %d sent sucessfully"), code);
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("EyeServer: eventmarker %d not sent"), code);
	}

}

void UEyeServerBPLibrary::AcceptiRecPoint()
{
	UE_LOG(LogTemp, Display, TEXT("EyeServer: Accept Calibration point"));
	DWORD result = EyeServerInterface::AcceptiRecCalibrationPoint();
	if (result == S_OK) {
		UE_LOG(LogTemp, Display, TEXT("EyeServer: accepted point ok"));
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("EyeServer: point not accepted"));
	}

}
