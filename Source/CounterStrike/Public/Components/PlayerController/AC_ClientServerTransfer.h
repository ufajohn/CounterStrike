// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Classes/Callbacks/CB_RegisterUser.h"
#include "Components/ActorComponent.h"
#include "Structs/RegisterUserStruct.h"
#include "AC_ClientServerTransfer.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COUNTERSTRIKE_API UAC_ClientServerTransfer : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UAC_ClientServerTransfer();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	void RequestRegisterUser(const FRegisterUserData& RegisterUserData, const FDelegateCallbackRequestRegisterUser& Callback);

	UFUNCTION(Server, Reliable)
	void Server_RequestRegisterUser(const FRegisterUserData& RegisterUserData);

	UFUNCTION(Client, Reliable)
	void Client_ResponseRegisterUser(bool Success, const TArray<FServersInfo>& ServersInfo);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;	

private:
	void ResponseRegisterUserFromDB(bool Success, const TArray<FServersInfo>& ServersInfo);
	FCallbackRequestRegisterUser CallbackRequestRegisterUser;
		
};
