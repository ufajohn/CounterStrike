// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "UObject/NoExportTypes.h"
#include "ServerPrivatInfoStruct.generated.h"

USTRUCT(BlueprintType)
struct FServerPrivateInfo
{
	GENERATED_BODY()

public:

	FServerPrivateInfo(){}
	
	FServerPrivateInfo(int32 NewID):
	ID(NewID)
	{		
	}

	FServerPrivateInfo(FString NewName, FString NewLevelName, FString NewAddress, bool ToDestroy):	
	Name(NewName),
	LevelName(NewLevelName),
	Address(NewAddress),
	bToDestroy(ToDestroy)
	{		
	}

	FServerPrivateInfo(int32 NewID, FString NewName, FString NewLevelName, FString NewAddress):
	ID(NewID),
	Name(NewName),
	LevelName(NewLevelName),
	Address(NewAddress)
	{		
	}

	FServerPrivateInfo(int32 NewID, FString NewName, FString NewLevelName, FString NewAddress, bool ToDestroy):
	ID(NewID),
	Name(NewName),
	LevelName(NewLevelName),
	Address(NewAddress),
	bToDestroy(ToDestroy)
	{		
	}

	

	UPROPERTY(BlueprintReadOnly)
	int32 ID = 0;

	UPROPERTY(BlueprintReadOnly)
	FString Name = "";

	UPROPERTY(BlueprintReadOnly)
	FString LevelName = "";

	UPROPERTY(BlueprintReadOnly)
	FString Address = "";

	UPROPERTY(BlueprintReadOnly)
	bool bToDestroy = false;
};
