// Fill out your copyright notice in the Description page of Project Settings.


#include "MainFunctions.h"
#include "GenericPlatform/GenericPlatformProcess.h"

void UMainFunctions::LaunchServer(const FString& MapAddress, const FString& Attributes)
{
	FString ResultAttributes = MapAddress + " " + Attributes + " -log";
	FString Url = FPaths::ProjectDir() + "Binaries/Win64/CounterStrikeServer.exe";
	
	FPlatformProcess::CreateProc(*Url, *ResultAttributes, true, false, false, nullptr, 0, nullptr, nullptr);
	
}
