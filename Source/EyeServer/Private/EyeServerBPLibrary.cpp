// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "EyeServerBPLibrary.h"
#include "EyeServer.h"
#include "EyeServerInterface.h"
#include "Windows/MinWindows.h"

UEyeServerBPLibrary::UEyeServerBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

void UEyeServerBPLibrary::Connect()
{
	UE_LOG(LogTemp, Display, TEXT("Connect to EyeServer"));
	ensureMsgf(EyeServerInterface::Connect() == 0,
		TEXT("Could not connect to DaqServer"));
}

void UEyeServerBPLibrary::Disconnect()
{
	UE_LOG(LogTemp, Display, TEXT("Disconnect from EyeServer"));
	if (EyeServerInterface::Disconnect() != S_OK) {
		UE_LOG(LogTemp, Warning, TEXT("Disconnect from EyeServer may have failed"));
	}
}
