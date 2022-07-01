// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "WebRequestBase.generated.h"


//DECLARE_LOG_CATEGORY_EXTERN(LogWebRequest, Log, All);


UENUM()
enum class EWebRequestType : uint8
{
	Post,
	Get
};


UCLASS()
class COUNTERSTRIKE_API UWebRequestBase : public UObject
{
	GENERATED_BODY()
	
protected:	
	bool CallWebScript(const FString& ScriptURL, TSharedPtr<FJsonObject>& JsonRequest, EWebRequestType RequestType = EWebRequestType::Post);
	
	TSharedPtr<FJsonObject> CreateJsonRequest();
	virtual void CallJsonResponse(const TSharedPtr<FJsonObject>& JsonResponse) {};
	virtual void CallJsonFail() {};
	virtual void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool WasSuccessful);	

private:	
	void InitRequest(TSharedRef<IHttpRequest, ESPMode::ThreadSafe> &Request, const FString& RequestType, const FString& ScriptURL);
	FHttpModule *Http;
	FString JsonStream = "JsonStream";
	bool bUsingSSL = false;	
};