// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PlayerController/AC_DatabaseTransfer.h"

// Sets default values for this component's properties
UAC_DatabaseTransfer::UAC_DatabaseTransfer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAC_DatabaseTransfer::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAC_DatabaseTransfer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAC_DatabaseTransfer::RegisterUser(const FRegisterUserData& RegisterUserData, const FDelegateCallbackRequestRegisterUser& Callback)
{
	//todo сделать проверки на данные пользователя при регистрации
	CallbackRequestRegisterUser.DelegateCallbackRequestRegisterUser = Callback;
}

