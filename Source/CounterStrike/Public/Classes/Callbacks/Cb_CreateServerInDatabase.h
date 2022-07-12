// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Cb_CreateServerInDatabase.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FDelegateCallbackRequestCreateGameServer, int32, NewServerID);

USTRUCT()
struct FCallbackRequestCreateGameServerInDB
{
	GENERATED_BODY()

	FCallbackRequestCreateGameServerInDB(){}

	FCallbackRequestCreateGameServerInDB( const FDelegateCallbackRequestCreateGameServer& Callback): DelegateCallbackRequestCreateGameServer(Callback){}

	UPROPERTY()
	FDelegateCallbackRequestCreateGameServer DelegateCallbackRequestCreateGameServer = FDelegateCallbackRequestCreateGameServer();
};



