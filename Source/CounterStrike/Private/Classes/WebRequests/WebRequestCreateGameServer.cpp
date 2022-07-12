// Fill out your copyright notice in the Description page of Project Settings.


#include "Classes/WebRequests/WebRequestCreateGameServer.h"


UWebRequestCreateGameServer* UWebRequestCreateGameServer::Create(UObject* Owner, const FString& ScriptURL,
	const FString& Name, const FString& LevelName, const FString& Address,
	const FDelegateCallbackRequestCreateGameServer& Callback)
{
	UWebRequestCreateGameServer* Obj = NewObject<UWebRequestCreateGameServer>(Owner);
	if(Obj)
	{
		Obj->Init(ScriptURL, Name, LevelName, Address, Callback);
		return  Obj;
	}
	return nullptr;
}

void UWebRequestCreateGameServer::Init(const FString& ScriptURL, const FString& Name, const FString& LevelName,
	const FString& Address, const FDelegateCallbackRequestCreateGameServer& Callback)
{
	CallbackRequestCreateGameServerInDB.DelegateCallbackRequestCreateGameServer = Callback;

	TSharedPtr<FJsonObject> Json = CreateJsonRequest();
	Json->SetStringField("ServerName", Name);
	Json->SetStringField("LevelName", LevelName);
	Json->SetStringField("ServerAddress", Address);

	CallWebScript(ScriptURL, Json);
}

void UWebRequestCreateGameServer::CallJsonResponse(const TSharedPtr<FJsonObject>& JsonResponse)
{
	//Super::CallJsonResponse(JsonResponse);
	FString Error = "";
	JsonResponse->TryGetStringField("Error", Error);

	if(!Error.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("[UWebRequestCreateGameServer::CallJsonResponse] %s"), *Error);
	}

	int32 Result = JsonResponse->GetIntegerField("Result");
	bool b = CallbackRequestCreateGameServerInDB.DelegateCallbackRequestCreateGameServer.ExecuteIfBound(Result);
}

void UWebRequestCreateGameServer::CallJsonFail()
{
	//Super::CallJsonFail();
	bool b = CallbackRequestCreateGameServerInDB.DelegateCallbackRequestCreateGameServer.ExecuteIfBound(0);
}
