// Fill out your copyright notice in the Description page of Project Settings.


#include "Classes/WebRequests/WebRequestGetIPAddress.h"

UWebRequestGetIPAddress* UWebRequestGetIPAddress::Create(UObject* Owner, const FString& ScriptURL,
	const FDelegateCallbackRequestGameServerAddress& Callback)
{
	UWebRequestGetIPAddress* Obj = NewObject<UWebRequestGetIPAddress>(Owner);
	if(Obj)
	{
		Obj->Init(ScriptURL, Callback);
		return Obj;		
	}
	else return nullptr;
}

void UWebRequestGetIPAddress::CallJsonResponse(const TSharedPtr<FJsonObject>& JsonResponse)
{
	FString IPAddress = "";
	if(JsonResponse->HasField("ip"))
	{
		IPAddress = JsonResponse->GetStringField("ip");
	}
	bool Result = CallbackRequestGameServerAddress.DelegateCallbackRequestGameServerAddress.ExecuteIfBound(IPAddress);
}

void UWebRequestGetIPAddress::CallJsonFail()
{
	bool Result = CallbackRequestGameServerAddress.DelegateCallbackRequestGameServerAddress.ExecuteIfBound("");	
}

void UWebRequestGetIPAddress::Init(const FString& ScriptURL, const FDelegateCallbackRequestGameServerAddress& Callback)
{
	CallbackRequestGameServerAddress.DelegateCallbackRequestGameServerAddress = Callback;

	TSharedPtr<FJsonObject> Json = CreateJsonRequest();
	
	CallWebScript(ScriptURL, Json);
}
