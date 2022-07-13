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
		
		FServerPrivateInfo Info = FServerPrivateInfo(Name, LevelName, Address, ToDestroy);

		bool Result = CallbackRequestGetServerInfoFromDB.DelegateCallbackRequestGetServerInfoFromDB.ExecuteIfBound(Info);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[UWebRequestGetServerInfoFromDB::CallJsonResponse] Failed response! Error: %s"), *ErrorString);
		bool Result = CallbackRequestGetServerInfoFromDB.DelegateCallbackRequestGetServerInfoFromDB.ExecuteIfBound(FServerPrivateInfo());
	}
}

void UWebRequestGetServerInfoFromDB::CallJsonFail()
{
	//Super::CallJsonFail();
	bool Result = CallbackRequestGetServerInfoFromDB.DelegateCallbackRequestGetServerInfoFromDB.ExecuteIfBound(FServerPrivateInfo());
}

void UWebRequestGetServerInfoFromDB::Init(const FString& ScriptURL, int32 ServerID,
	const FDelegateCallbackRequestGetServerInfoFromDB& Callback)
{
	CallbackRequestGetServerInfoFromDB.DelegateCallbackRequestGetServerInfoFromDB = Callback;

	TSharedPtr<FJsonObject> Json = CreateJsonRequest();
	Json->SetNumberField("ServerID", (double)ServerID);

	CallWebScript(ScriptURL, Json);
}
