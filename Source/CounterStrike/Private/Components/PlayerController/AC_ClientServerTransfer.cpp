// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PlayerController/AC_ClientServerTransfer.h"

#include "Components/PlayerController/AC_DatabaseTransfer.h"

// Sets default values for this component's properties
UAC_ClientServerTransfer::UAC_ClientServerTransfer()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);

}


void UAC_ClientServerTransfer::Client_ResponseRegisterUser_Implementation(bool Success,	const TArray<FServersInfo>& ServersInfo)
{
	bool Result = CallbackRequestRegisterUser.DelegateCallbackRequestRegisterUser.ExecuteIfBound(Success, ServersInfo);	
}

// Called when the game starts
void UAC_ClientServerTransfer::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UAC_ClientServerTransfer::ResponseRegisterUserFromDB(bool Success, const TArray<FServersInfo>& ServersInfo)
{
	Client_ResponseRegisterUser(Success, ServersInfo);
}

// Called every frame
void UAC_ClientServerTransfer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAC_ClientServerTransfer::RequestRegisterUser(const FRegisterUserData& RegisterUserData, const FDelegateCallbackRequestRegisterUser& Callback)
{
	CallbackRequestRegisterUser.DelegateCallbackRequestRegisterUser = Callback;

	Server_RequestRegisterUser(RegisterUserData);
}

void UAC_ClientServerTransfer::Server_RequestRegisterUser_Implementation(const FRegisterUserData& RegisterUserData)
{
	FDelegateCallbackRequestRegisterUser DelegateCallbackRequestRegisterUser;
	DelegateCallbackRequestRegisterUser.BindUFunction(this, "ResponseRegisterUserFromDB");
	//todo создать ResponseRegisterUserFromDB

	UAC_DatabaseTransfer* DatabaseTransfer = GetOwner()->FindComponentByClass<UAC_DatabaseTransfer>();
	if(DatabaseTransfer)
	{
		DatabaseTransfer->RegisterUser(RegisterUserData, DelegateCallbackRequestRegisterUser);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'UAC_DatabaseTransfer' component not found in '%s'!"), *GetOwner()->GetName());
	}
}

