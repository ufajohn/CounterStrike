// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs/ServersInfoStruct.h"
#include "CB_RegisterUser.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FDelegateCallbackRequestRegisterUser, bool, Success, const TArray<FServersInfo>&, ServerList);

USTRUCT()
struct FCallbackRequestRegisterUser
{
	GENERATED_BODY()
	
	FCallbackRequestRegisterUser(): DelegateCallbackRequestRegisterUser(FDelegateCallbackRequestRegisterUser()){}
    FCallbackRequestRegisterUser(const FDelegateCallbackRequestRegisterUser& Callback): DelegateCallbackRequestRegisterUser(Callback){}
    
    UPROPERTY()
    FDelegateCallbackRequestRegisterUser DelegateCallbackRequestRegisterUser;
	
	
};


