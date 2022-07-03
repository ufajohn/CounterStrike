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
	// Sets default values for this component's properties
	UAC_DatabaseTransfer();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void RegisterUser(const FRegisterUserData& RegisterUserData, const FDelegateCallbackRequestRegisterUser& Callback);

private: FCallbackRequestRegisterUser CallbackRequestRegisterUser;
	
};
