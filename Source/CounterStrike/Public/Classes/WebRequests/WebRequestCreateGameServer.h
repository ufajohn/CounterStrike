// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Classes/WebRequestBase.h"
#include "Classes/Callbacks/Cb_CreateServerInDatabase.h"
#include "WebRequestCreateGameServer.generated.h"

/**
 * 
 */
UCLASS()
class COUNTERSTRIKE_API UWebRequestCreateGameServer : public UWebRequestBase
{
	GENERATED_BODY()
	
public:
	
    static UWebRequestCreateGameServer* Create(UObject* Owner, const FString& ScriptURL, const FString& Name, const FString& LevelName, const FString& Address, const FDelegateCallbackRequestCreateGameServer& Callback);
	static UWebRequestCreateGameServer* Remove(UObject* Owner, const FString& ScriptURL, int32 ServerID);

private:
	void Init(const FString& ScriptURL, const FString& Name, const FString& LevelName, const FString& Address, const FDelegateCallbackRequestCreateGameServer& Callback);

	void InitRemove(const FString& ScriptURL, int32 ServerID);

	FCallbackRequestCreateGameServerInDB CallbackRequestCreateGameServerInDB;

protected:
	virtual void CallJsonResponse(const TSharedPtr<FJsonObject>& JsonResponse) override;
	virtual void CallJsonFail() override;
};
