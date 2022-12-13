// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Classes/Callbacks/Cb_CreateServerInDatabase.h"
#include "Classes/Callbacks/Cb_RequestGameServerAddress.h"
#include "Components/ActorComponent.h"
#include "Structs/ServerPrivatInfoStruct.h"
#include "AC_GameServerDatabase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COUNTERSTRIKE_API UAC_GameServerDatabase : public UActorComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(Blueprintcallable)
	bool GetLobby();
	
	// Sets default values for this component's properties
	UAC_GameServerDatabase();

	UFUNCTION(Blueprintcallable)
	void CallGameServerURL(const FDelegateCallbackRequestGameServerAddress& Callback);

	UFUNCTION(Blueprintcallable)
	void CreateServerToDB();

	UFUNCTION(Blueprintcallable)
	void RemoveServerFromDB();

	UPROPERTY(BlueprintReadOnly)
	bool bServerFound = false;	

	UPROPERTY(BlueprintReadOnly)
	FString ServerSocket = "";	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UFUNCTION(BlueprintCallable)
	void GetServerDataFromDB();

	UFUNCTION(BlueprintCallable)
	void ConnectToServer();

	UFUNCTION(BlueprintCallable)
	void ShutDownServer();
	
	UFUNCTION()
	void ResponseGameServerAddress(const FString& Address);

	UFUNCTION()
	void ResponseCreateServerToDB(int32 NewServerID);

	UFUNCTION()
	void ResponseGetServerInfoFromDB(const FServerPrivateInfo& Info);

	FString ServerAddress;
	int32 ServerPort;
	FString CreateProcessURL;
	FString CreateServerURL;
	FString RemoveServerURL;
	FString GetIPAddressURL;
	FString GetServerPrivateInfoAddressURL;
	FString LobbyURL;
	
	FString LevelName;
	FString ServerName;

	//информация о сервере из БД
	FServerPrivateInfo ServerInfo;

	//коллбак на получение данных о сервере из БД
	UPROPERTY()
	FCallbackRequestCreateGameServerInDB CallbackRequestCreateGameServerInDB;

	//True, если запрос на получение данных из БД уже отправлен
	bool bAlreadyRequestGetServerInfoFromDB;

	//TRUE, если внешний адрес получен через опции ярлыка запуска
	bool bCommitedAddressFromOption;

	//True, если сервер успешно прописал себя в БД и стал активным
	bool bActivatedServer;

	

	UPROPERTY()
	FCallbackRequestGameServerAddress CallbackRequestGameServerAddress;
		
};



