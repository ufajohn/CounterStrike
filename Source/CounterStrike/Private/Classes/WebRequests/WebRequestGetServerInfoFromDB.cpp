// Fill out your copyright notice in the Description page of Project Settings.


#include "Classes/WebRequests/WebRequestGetServerInfoFromDB.h"

UWebRequestGetServerInfoFromDB* UWebRequestGetServerInfoFromDB::Create(UObject* Owner, const FString& ScriptURL,
	int32 ServerID, const FDelegateCallbackRequestGetServerInfoFromDB& Callback)
{
	UWebRequestGetServerInfoFromDB* Obj = NewObject<UWebRequestGetServerInfoFromDB>(Owner);
	if(!Obj) return nullptr;

	Obj->Init(ScriptURL, ServerID, Callback);

	return Obj;
}

void UWebRequestGetServerInfoFromDB::CallJsonResponse(const TSharedPtr<FJsonObject>& JsonResponse)
{
	//Super::CallJsonResponse(JsonResponse);
	FString ErrorString = "";

	if(JsonResponse->HasField("Error"))
	{
		ErrorString = JsonResponse->GetStringField("Error");
	}

	if(ErrorString.IsEmpty())
	{
		FString Name = JsonResponse->GetStringField("Name");
		FString LevelName = JsonResponse->GetStringField("LevelName");
		FString Address = "";
		{
			FString Left;
			FString Right;
			JsonResponse->GetStringField("Address").Split(":", &Left, &Right);
			Address = Left;		
		}
		bool ToDestroy = JsonResponse->GetBoolField("ToDestroy");
	}
}

void UWebRequestGetServerInfoFromDB::CallJsonFail()
{
	Super::CallJsonFail();
}

void UWebRequestGetServerInfoFromDB::Init(const FString& ScriptURL, int32 ServerID,
	const FDelegateCallbackRequestGetServerInfoFromDB& Callback)
{
}
