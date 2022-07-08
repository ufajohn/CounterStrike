// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Classes/Callbacks/CB_RegisterUser.h"
#include "Components/ActorComponent.h"
#include "Structs/RegisterUserStruct.h"
#include "AC_DatabaseTransfer.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COUNTERSTRIKE_API UAC_DatabaseTransfer : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UAC_DatabaseTransfer();
	
	void RegisterUser(const FRegisterUserData& RegisterUserData, const FDelegateCallbackRequestRegisterUser& Callback);

private:
	UFUNCTION()
	void WebResponseRegisterUser(bool Success, const TArray<FServersInfo>& ServersInfo);
	FCallbackRequestRegisterUser CallbackRequestRegisterUser;
	FString RegisterUserURL;
	
};
