// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MainFunctions.generated.h"

/**
 * 
 */
UCLASS()
class COUNTERSTRIKE_API UMainFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Server Functions")
	static void LaunchServer(const FString& MapAddress, const FString& Attributes);
	
};
