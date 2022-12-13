// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GameMode/AC_GameServerDatabase.h"

#include "Classes/WebRequestBaseBP.h"
#include "Classes/Callbacks/Cb_CreateServerInDatabase.h"
#include "Classes/Callbacks/Cb_RequestGetServerInfoFromDB.h"
#include "Classes/WebRequests/WebRequestCreateGameServer.h"
#include "Classes/WebRequests/WebRequestGetIPAddress.h"
#include "Classes/WebRequests/WebRequestGetServerPrivateInfo.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"


UAC_GameServerDatabase::UAC_GameServerDatabase()
{	
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 1.f;

	CreateServerURL = "greenstrike.ru/phpscripts/CreateServer.php";
	RemoveServerURL = "greenstrike.ru/phpscripts/RemoveServer.php";
	GetIPAddressURL = "greenstrike.ru/phpscripts/GetIP.php";
	GetServerPrivateInfoAddressURL = "greenstrike.ru/phpscripts/GetServerPrivateInfoAddressURL.php";
	LobbyURL = "greenstrike.ru/phpscripts/GetLobby.php";
}

void UAC_GameServerDatabase::CallGameServerURL(const FDelegateCallbackRequestGameServerAddress& Callback)
{
	UWebRequestGetIPAddress* Obj = UWebRequestGetIPAddress::Create(GetOwner(), GetIPAddressURL, Callback);
	if(!Obj)
	{
		UE_LOG(LogTemp, Error, TEXT("Fail to create object 'UWebRequestGetIPAddress'!"));
		bool Result = Callback.ExecuteIfBound("");
	}
}

bool UAC_GameServerDatabase::GetLobby()
{
	bool success;
	FDelegateCallbackRequestGetServerInfoFromDB Callback;
	Callback.BindUFunction(this, "ResponseGetServerInfoFromDB");

	UWebRequestGetServerPrivateInfo* WebRequestGetServerPrivateInfo = UWebRequestGetServerPrivateInfo::Create(GetOwner(), LobbyURL, ServerInfo.ID, Callback);
		
	if(!WebRequestGetServerPrivateInfo)
	{
		UE_LOG(LogTemp, Error, TEXT("Fail to create object 'UWebRequestGetServerPrivateInfo'!"));
		bool r = Callback.ExecuteIfBound(FServerPrivateInfo());
		success = false;
	}
	else success = true;
	
	return success;	
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
	//FDelegateCallbackRequestCreateGameServer DelegateCallbackRequestRemoveGameServer;
	//DelegateCallbackRequestRemoveGameServer.BindUFunction(this, "ResponseRemoveServerFromDB");

	UWebRequestCreateGameServer* Obj = UWebRequestCreateGameServer::Remove(GetOwner(), RemoveServerURL, ServerInfo.ID);
	if(!Obj)
	{
		UE_LOG(LogTemp, Error, TEXT("Fail to create object 'UWebRequestCreateGameServer'!"));		
	}	
}

void UAC_GameServerDatabase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	RemoveServerFromDB();

	Super::EndPlay(EndPlayReason);	
}

void UAC_GameServerDatabase::GetServerDataFromDB()
{
	//if(!bActivatedServer) return;
	//if(bAlreadyRequestGetServerInfoFromDB) return;
	
	FDelegateCallbackRequestGetServerInfoFromDB Callback;
	Callback.BindUFunction(this, "ResponseGetServerInfoFromDB");

	UWebRequestGetServerPrivateInfo* WebRequestGetServerPrivateInfo = UWebRequestGetServerPrivateInfo::Create(GetOwner(), GetServerPrivateInfoAddressURL, ServerInfo.ID, Callback);

	if(!WebRequestGetServerPrivateInfo)
	{
		UE_LOG(LogTemp, Error, TEXT("Fail to create object 'UWebRequestGetServerPrivateInfo'!"));
		bool r = Callback.ExecuteIfBound(FServerPrivateInfo());
	}
}

void UAC_GameServerDatabase::ConnectToServer()
{
	
}

void UAC_GameServerDatabase::ResponseGetServerInfoFromDB(const FServerPrivateInfo& Info)
{
	if(Info.bToDestroy)
	{
		bServerFound = false;
		ShutDownServer();
		return;
	}
	
	FServerPrivateInfo NewInfo = Info;
	NewInfo.ID = ServerInfo.ID;

	FString NewAddress;
	FString NewPort;
	Info.Address.Split(":", &NewAddress, &NewPort);

	ServerSocket = Info.Address;
	NewInfo.Address = NewAddress;
	NewInfo.LevelName = ServerInfo.LevelName;

	if(NewInfo.Name == "")
	{
		bServerFound = false;
		return;
	}		
	bServerFound = true;

	ServerInfo = NewInfo;
	bAlreadyRequestGetServerInfoFromDB = false;
	
}

void UAC_GameServerDatabase::ShutDownServer()
{
	RemoveServerFromDB();
	
	RequestEngineExit("ShutdownGameServer");
}

void UAC_GameServerDatabase::ResponseGameServerAddress(const FString& Address)
{
	ServerAddress = Address;
	ServerPort = GetWorld()->URL.Port;

	UE_LOG(LogTemp, Log, TEXT("Response server address: %s:%d"), *ServerAddress, ServerPort);

	CreateServerToDB();
}

void UAC_GameServerDatabase::ResponseCreateServerToDB(int32 NewServerID)
{
UE_LOG(LogTemp, Log, TEXT("Server added to Database %s"), NewServerID > 0 ? TEXT("success") : TEXT("fail"))
	
	if(NewServerID > 0)
	{
		ServerInfo = FServerPrivateInfo(NewServerID, ServerName, LevelName, ServerAddress);
		bActivatedServer = true;
	}
	else
	{
		ShutDownServer();
	}
}




void UAC_GameServerDatabase::BeginPlay()
{
	Super::BeginPlay();

	AGameModeBase* GameModeBase = Cast<AGameModeBase>(GetOwner());

	if (!GameModeBase)
	{
		UE_LOG(LogTemp, Log, TEXT("GameModeBase FAIL %s"), GameModeBase);
		return;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("GameModeBase SUCCESS %s"), GameModeBase);
	}
	
	
	
	ServerName = UGameplayStatics::ParseOption(GameModeBase->OptionsString, "ServerName");
	//UE_LOG(LogTemp, Log, TEXT("ServerName %s"), ServerName);

	

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

	//GetServerDataFromDB();
}

