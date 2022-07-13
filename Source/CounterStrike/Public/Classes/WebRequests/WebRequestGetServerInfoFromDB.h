// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Classes/WebRequestBase.h"
#include "Classes/Callbacks/Cb_RequestGetServerInfoFromDB.h"
#include "WebRequestGetServerInfoFromDB.generated.h"

/**
 * 
 */
UCLASS()
class COUNTERSTRIKE_API UWebRequestGetServerInfoFromDB : public UWebRequestBase
{
	GENERATED_BODY()

public:
	static UWebRequestGetServerInfoFromDB* Create(UObject* Owner, const FString& ScriptURL, int32 ServerID, const FDelegateCallbackRequestGetServerInfoFromDB& Callback);

protected:
	virtual void CallJsonResponse(const TSharedPtr<FJsonObject>& JsonResponse) override;
	virtual void CallJsonFail() override;

private:
	void Init(const FString& ScriptURL, int32 ServerID, const FDelegateCallbackRequestGetServerInfoFromDB& Callback);
	FCallbackRequestGetServerInfoFromDB CallbackRequestGetServerInfoFromDB;
	
};
