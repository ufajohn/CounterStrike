// Fill out your copyright notice in the Description page of Project Settings.


#include "Classes/WebRequests/WebRequestRegisterUser.h"

#include "Structs/ServersInfoStruct.h"

UWebRequestRegisterUser* UWebRequestRegisterUser::Create(UObject* Owner, const FRegisterUserData& Data,
                                                         const FDelegateCallbackRequestRegisterUser& Callback)
{
	UWebRequestRegisterUser* Obj = NewObject<UWebRequestRegisterUser>(Owner);
	Obj->Init(Data, Callback);
	return  Obj;	
}

void UWebRequestRegisterUser::CallJsonResponse(const TSharedPtr<FJsonObject>& JsonResponse)
{
	//Super::CallJsonResponse(JsonResponse);
	bool Success = JsonResponse->GetBoolField("Success");
	TArray<FServersInfo> ServerInfo;
	if(!Success)
	{
		bool Result = CallbackRequestRegisterUser.DelegateCallbackRequestRegisterUser.ExecuteIfBound(Success, ServerInfo);
		return;
	}
	TArray<FString> Names;
	TArray<FString> Address;

	JsonResponse->TryGetStringArrayField("ServerNames", Names);
	JsonResponse->TryGetStringArrayField("ServerAddress", Address);

	for(int32 i = 0; i < Names.Num(); i++)
	{
		ServerInfo.Add(FServersInfo(Names[i], Address[i]));
	}
	bool Result = CallbackRequestRegisterUser.DelegateCallbackRequestRegisterUser.ExecuteIfBound(Success, ServerInfo);
	
}

void UWebRequestRegisterUser::CallJsonFail()
{
	//Super::CallJsonFail();
	bool Result = CallbackRequestRegisterUser.DelegateCallbackRequestRegisterUser.ExecuteIfBound(false, TArray<FServersInfo>());
}

void UWebRequestRegisterUser::Init(const FRegisterUserData& Data, const FDelegateCallbackRequestRegisterUser& Callback)
{
	CallbackRequestRegisterUser.DelegateCallbackRequestRegisterUser = Callback;
	
	TSharedPtr<FJsonObject> Json = CreateJsonRequest();
	Json->SetStringField("UserLogin", Data.Login);
	Json->SetStringField("UserPassword", Data.Password);

	CallWebScript("worldgreenplace.ddns.net/registeruser.php", Json);
	
}
