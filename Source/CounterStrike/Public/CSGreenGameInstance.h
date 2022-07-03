// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CSGreenGameInstance.generated.h"


UCLASS()
class COUNTERSTRIKE_API UCSGreenGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UCSGreenGameInstance();
	
	virtual void Init() override;
	
	UFUNCTION(BlueprintCallable)
	void CreateSession();

	void OnCreateSessionComplete(FName SessioName, bool bWasSuccessful);
	
	//UFUNCTION(BlueprintCallable)
	void Login();

	void OnLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);

protected:
	class IOnlineSubsystem* OnlineSubsystem;

	bool bIsLoggedIn;

};
