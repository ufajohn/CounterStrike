// Fill out your copyright notice in the Description page of Project Settings.


#include "Classes/WebRequests/WebRequestRegisterUser.h"

#include "Structs/ServersInfoStruct.h"

UWebRequestRegisterUser* UWebRequestRegisterUser::Create(UObject* Owner, const FString& ScriptURL, const FRegisterUserData& Data, const FDelegateCallbackRequestRegisterUser& Callback)
{
	UWebRequestRegisterUser* Obj = NewObject<UWebRequestRegisterUser>(Owner);
	Obj->Init(ScriptURL, Data, Callback);
	return  Obj;	
}

void UWebRequestRegisterUser::CallJsonResponse(const TSharedPtr<FJsonObject>& JsonResponse)
{
	//Super::CallJsonResponse(JsonResponse);
	bool Success = JsonResponse->GetBoolField("Success");
	TArray<FServersInfo> ServersInfo;
	if(!Success)
	{
		bool Result = CallbackRequestRegisterUser.DelegateCallbackRequestRegisterUser.ExecuteIfBound(Success, ServersInfo);
		return;
	}
	TArray<FString> Names;
	TArray<FString> Addresses;

	JsonResponse->TryGetStringArrayField("ServerNames", Names);
	JsonResponse->TryGetStringArrayField("ServerAddresses", Addresses);

	for(int32 i = 0; i < Names.Num(); i++)
	{
		ServersInfo.Add(FServersInfo(Names[i], Addresses[i]));
	}
	bool Result = CallbackRequestRegisterUser.DelegateCallbackRequestRegisterUser.ExecuteIfBound(Success, ServersInfo);
	
}

void UWebRequestRegisterUser::CallJsonFail()
{
	//Super::CallJsonFail();
	bool Result = CallbackRequestRegisterUser.DelegateCallbackRequestRegisterUser.ExecuteIfBound(false, TArray<FServersInfo>());
}

void UWebRequestRegisterUser::Init(const FString& ScriptURL, const FRegisterUserData& Data, const FDelegateCallbackRequestRegisterUser& Callback)
{
	CallbackRequestRegisterUser.DelegateCallbackRequestRegisterUser = Callback;
	
	TSharedPtr<FJsonObject> Json = CreateJsonRequest();
	Json->SetStringField("UserLogin", Data.Login);
	Json->SetStringField("UserPassword", Data.Password);

	CallWebScript(ScriptURL, Json);
	
}
