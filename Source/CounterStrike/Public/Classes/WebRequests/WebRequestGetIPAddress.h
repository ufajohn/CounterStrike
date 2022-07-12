// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Classes/WebRequestBase.h"
#include "Classes/Callbacks/Cb_RequestGameServerAddress.h"
#include "WebRequestGetIPAddress.generated.h"

/**
 * 
 */
UCLASS()
class COUNTERSTRIKE_API UWebRequestGetIPAddress : public UWebRequestBase
{
	GENERATED_BODY()

public:
	static UWebRequestGetIPAddress* Create(UObject* Owner, const FString& ScriptURL, const FDelegateCallbackRequestGameServerAddress& Callback);

protected:
	virtual void CallJsonResponse(const TSharedPtr<FJsonObject>& JsonResponse) override;
	virtual void CallJsonFail() override;

private:
	void Init(const FString& ScriptURL, const FDelegateCallbackRequestGameServerAddress& Callback);

	FCallbackRequestGameServerAddress CallbackRequestGameServerAddress;
};
