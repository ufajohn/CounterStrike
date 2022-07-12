// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Classes/Callbacks/Cb_CreateServerInDatabase.h"
#include "Classes/Callbacks/Cb_RequestGameServerAddress.h"
#include "Components/ActorComponent.h"
#include "AC_GameServerDatabase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COUNTERSTRIKE_API UAC_GameServerDatabase : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_GameServerDatabase();

	void CallGameServerURL(const FDelegateCallbackRequestGameServerAddress& Callback);

	void CreateServerToDB();

	void RemoveServerFromDB();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	void GetServerDataFromDB();
	
	UFUNCTION()
	void ResponseGameServerAddress(const FString& Address);

	UFUNCTION()
	void ResponseCreateServerToDB(int32 NewServerID);

	void ResponseRemoveServerFromDB(bool Success);
	
	FString ServerAddress;
	int32 ServerPort;
	FString CreateServerURL;
	FString GetIPAddressURL;
	FString LevelName;
	FString ServerName;

	//TRUE, если внешний адрес получен через опции ярлыка запуска
	bool bCommitedAddressFromOption;

	UPROPERTY()
	FCallbackRequestGameServerAddress CallbackRequestGameServerAddress;
		
};
