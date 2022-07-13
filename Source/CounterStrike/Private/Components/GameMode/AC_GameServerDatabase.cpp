// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GameMode/AC_GameServerDatabase.h"
#include "Classes/Callbacks/Cb_CreateServerInDatabase.h"
#include "Classes/Callbacks/Cb_RequestGetServerInfoFromDB.h"
#include "Classes/WebRequests/WebRequestCreateGameServer.h"
#include "Classes/WebRequests/WebRequestGetIPAddress.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"


UAC_GameServerDatabase::UAC_GameServerDatabase()
{	
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 1.f;

	CreateServerURL = "worldgreenplace.ddns.net/phpscripts/CreateServer.php";
	GetIPAddressURL = "worldgreenplace.ddns.net/phpscripts/GetIP.php";
}

void UAC_GameServerDatabase::CallGameServerURL(const FDelegateCallbackRequestGameServerAddress& Callback)
{
	UWebRequestGetIPAddress* Obj = UWebRequestGetIPAddress::Create(GetOwner(), GetIPAddressURL, Callback);
	if(!Obj)
	{
		UE_LOG(LogTemp, Error, TEXT("Fail to create object 'UWebRequestGetIPAddress'!"));
		bool Result = Callback.ExecuteIfBound(0);
	}
}

void UAC_GameServerDatabase::CreateServerToDB()
{
	FDelegateCallbackRequestCreateGameServer DelegateCallbackRequestCreateGameServer;
	DelegateCallbackRequestCreateGameServer.BindUFunction(this, "ResponseCreateServerToDB");

	UWebRequestCreateGameServer* Obj = UWebRequestCreateGameServer::Create(GetOwner(), CreateServerURL, ServerName, LevelName, ServerAddress + ":" + FString::FromInt(ServerPort), DelegateCallbackRequestCreateGameServer);
	if(!Obj)
	{
		UE_LOG(LogTemp, Error, TEXT("Fail to create object 'UWebRequestCreateGameServer'!"));
		bool Result = DelegateCallbackRequestCreateGameServer.ExecuteIfBound(0);
	}
}

void UAC_GameServerDatabase::RemoveServerFromDB()
{
	FDelegateCallbackRequestCreateGameServer DelegateCallbackRequestRemoveGameServer;
	DelegateCallbackRequestRemoveGameServer.BindUFunction(this, "ResponseRemoveServerFromDB");

	UWebRequestCreateGameServer* Obj = UWebRequestCreateGameServer::Remove(GetOwner(), CreateServerURL, ServerName, DelegateCallbackRequestRemoveGameServer);
	if(!Obj)
	{
		UE_LOG(LogTemp, Error, TEXT("Fail to create object 'UWebRequestCreateGameServer'!"));
		bool Result = DelegateCallbackRequestRemoveGameServer.ExecuteIfBound(false);
	}

}

void UAC_GameServerDatabase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	RemoveServerFromDB();

	Super::EndPlay(EndPlayReason);	
}

void UAC_GameServerDatabase::GetServerDataFromDB()
{
	FDelegateCallbackRequestGetServerInfoFromDB Callback;
	Callback.BindUFunction(this, "ResponseGetServerInfoFromDB");
}

void UAC_GameServerDatabase::ShutDownServer()
{
	RequestEngineExit("");
}

void UAC_GameServerDatabase::ResponseGameServerAddress(const FString& Address)
{
	ServerAddress = Address;
	ServerPort = GetWorld()->URL.Port;

	UE_LOG(LogTemp, Log, TEXT("Response server address: %s:%d"), *ServerAddress,ServerPort);

	CreateServerToDB();
}

void UAC_GameServerDatabase::ResponseCreateServerToDB(int32 NewServerID)
{
UE_LOG(LogTemp, Log, TEXT("Server added to Database %s"), NewServerID > 0 ? TEXT("success") : TEXT("fail"))
	
	if(NewServerID > 0)
	{
		ServerInfo = FServerPrivateInfo(NewServerID, ServerName, LevelName, ServerAddress);		
	}
	else
	{
		ShutDownServer();
	}
}

void UAC_GameServerDatabase::ResponseRemoveServerFromDB(bool Success)
{
	if(Success)
	{
		
	}
}


void UAC_GameServerDatabase::BeginPlay()
{
	Super::BeginPlay();

	AGameModeBase* GameModeBase = Cast<AGameModeBase>(GetOwner());
	if(!GameModeBase) return;
	
	ServerName = UGameplayStatics::ParseOption(GameModeBase->OptionsString, "ServerName");

	

	if (UWorld* World = GEngine->GetWorldFromContextObject(GetOwner(), EGetWorldErrorMode::LogAndReturnNull)) 
	{
		LevelName = World->GetMapName();
		LevelName.RemoveFromStart(World->StreamingLevelsPrefix);		
	}

	if(ServerName.IsEmpty())
	{
		ServerName = LevelName;
	}

	bCommitedAddressFromOption = UGameplayStatics::HasOption(GameModeBase->OptionsString, "IPAddress");
	if(bCommitedAddressFromOption)
	{
		ResponseGameServerAddress(UGameplayStatics::ParseOption(GameModeBase->OptionsString, "IPAddress"));
	}
	else
	{
		FDelegateCallbackRequestGameServerAddress DelegateCallbackRequestGameServerAddress;
		DelegateCallbackRequestGameServerAddress.BindUFunction(this, "ResponseGameServerAddress");
		CallGameServerURL(DelegateCallbackRequestGameServerAddress);
	}
	
}


// Called every frame
void UAC_GameServerDatabase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	GetServerDataFromDB();
}

