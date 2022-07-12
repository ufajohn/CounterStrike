// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Cb_RequestGameServerAddress.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FDelegateCallbackRequestGameServerAddress, const FString&, Address);

USTRUCT()
struct FCallbackRequestGameServerAddress
{
	GENERATED_BODY()

	FCallbackRequestGameServerAddress(){}

	FCallbackRequestGameServerAddress( const FDelegateCallbackRequestGameServerAddress& Callback): DelegateCallbackRequestGameServerAddress(Callback){}

	UPROPERTY()
	FDelegateCallbackRequestGameServerAddress DelegateCallbackRequestGameServerAddress = FDelegateCallbackRequestGameServerAddress();
};
