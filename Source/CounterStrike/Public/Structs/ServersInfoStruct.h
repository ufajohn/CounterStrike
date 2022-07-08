// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ServersInfoStruct.generated.h"

USTRUCT(BlueprintType)
struct FServersInfo
{
	GENERATED_BODY()
	FServersInfo(){}
	FServersInfo(const FString& NewName, const FString& NewAddress):Name(NewName), IPAddress(NewAddress){}

	UPROPERTY(BlueprintReadOnly)
	FString Name = "";

	UPROPERTY(BlueprintReadOnly)
	FString IPAddress = "";	
};