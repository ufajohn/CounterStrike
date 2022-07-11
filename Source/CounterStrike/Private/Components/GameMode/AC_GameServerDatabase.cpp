// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GameMode/AC_GameServerDatabase.h"

// Sets default values for this component's properties
UAC_GameServerDatabase::UAC_GameServerDatabase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CreateServerURL = "worldgreenplace.ddns.net/CreateServer.php";
}

void UAC_GameServerDatabase::CreateServerToDB()
{

}

void UAC_GameServerDatabase::RemoveServerFromDB()
{

}

void UAC_GameServerDatabase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	RemoveServerFromDB();

	Super::EndPlay(EndPlayReason);	
}


// Called when the game starts
void UAC_GameServerDatabase::BeginPlay()
{
	Super::BeginPlay();

	if (UWorld* World = GEngine->GetWorldFromContextObject(GetOwner(), EGetWorldErrorMode::LogAndReturnNull)) 
	{
		LevelName = World->GetMapName();
		LevelName.RemoveFromStart(World->StreamingLevelsPrefix);

		CreateServerToDB();
	}
	
}


// Called every frame
void UAC_GameServerDatabase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

