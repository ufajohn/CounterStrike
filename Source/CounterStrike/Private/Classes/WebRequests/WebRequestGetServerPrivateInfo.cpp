// Fill out your copyright notice in the Description page of Project Settings.


#include "Classes/WebRequests/WebRequestGetServerPrivateInfo.h"

#include "Android/AndroidRuntimeSettings/Classes/AndroidRuntimeSettings.h"

UWebRequestGetServerPrivateInfo* UWebRequestGetServerPrivateInfo::Create(UObject* Owner, const FString& ScriptURL,
                                                                         int32 ServerID, const FDelegateCallbackRequestGetServerInfoFromDB& Callback)
{
	UWebRequestGetServerPrivateInfo* Obj = NewObject<UWebRequestGetServerPrivateInfo>(Owner);
	if(!Obj) return nullptr;

	Obj->Init(ScriptURL, ServerID, Callback);
	return Obj;
}

void UWebRequestGetServerPrivateInfo::CallJsonResponse(const TSharedPtr<FJsonObject>& JsonResponse)
{
	//Super::CallJsonResponse(JsonResponse);
	FString ErrorString = "";
	if(JsonResponse->TryGetStringField("Error", ErrorString))
	{
		UE_LOG(LogTemp, Error, TEXT("[UWebRequestGetServerPrivateInfo::CallJsonResponse] Fail to json response: %s"), *ErrorString);
		bool s = CallbackRequestGetServerInfoFromDB.DelegateCallbackRequestGetServerInfoFromDB.ExecuteIfBound(FServerPrivateInfo());
		return;
	}

	FServerPrivateInfo Info;

	FString Address = JsonResponse->GetStringField("Address");
	FString Name = JsonResponse->GetStringField("Name");
	bool ToDestroy = JsonResponse->GetBoolField("ToDestroy");

	Info.Address = Address;
	Info.Name = Name;
	Info.bToDestroy = ToDestroy;

	bool s = CallbackRequestGetServerInfoFromDB.DelegateCallbackRequestGetServerInfoFromDB.ExecuteIfBound(Info);
}

void UWebRequestGetServerPrivateInfo::CallJsonFail()
{
	//Super::CallJsonFail();
	bool s = CallbackRequestGetServerInfoFromDB.DelegateCallbackRequestGetServerInfoFromDB.ExecuteIfBound(FServerPrivateInfo());
}

void UWebRequestGetServerPrivateInfo::Init(const FString& ScriptURL, int32 ServerID,
	const FDelegateCallbackRequestGetServerInfoFromDB& Callback)
{
	CallbackRequestGetServerInfoFromDB = Callback;

	TSharedPtr<FJsonObject> Json = CreateJsonRequest();
	Json->SetNumberField("ServerID", (double)ServerID);

	CallWebScript(ScriptURL, Json);
}
