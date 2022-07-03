// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Classes/Callbacks/CB_RegisterUser.h"
#include "Structs/RegisterUserStruct.h"
#include "UObject/NoExportTypes.h"
#include "WebRequestRegisterUser.generated.h"

/**
 * 
 */
UCLASS()
class COUNTERSTRIKE_API UWebRequestRegisterUser : public UObject
{
	GENERATED_BODY()
public:

	static  UWebRequestRegisterUser* Create(FRegisterUserData& Data, const FDelegateCallbackRequestRegisterUser&);
	
};
