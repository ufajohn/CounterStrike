// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Classes/WebRequestBase.h"
#include "WebRequestCreateGameServer.generated.h"

/**
 * 
 */
UCLASS()
class COUNTERSTRIKE_API UWebRequestCreateGameServer : public UWebRequestBase
{
	GENERATED_BODY()
	
public:
	
    static UWebRequestCreateGameServer* Create(UObject* Owner, const FString& ScriptURL, const FString& Name, const FString& LevelName, const FString& Address);
};
