// Fill out your copyright notice in the Description page of Project Settings.


#include "Classes/WebRequestBase.h"

DEFINE_LOG_CATEGORY(LogWebRequest);

bool UWebRequestBase::CallWebScript(const FString& ScriptURL, TSharedPtr<FJsonObject>& JsonRequest,
	EWebRequestType RequestType)
{
	if(!Http) Http = &FHttpModule::Get();
	TShaderRef<IHttpRequest> IhttpRequest = Http->CreateRequest();
	FString ResultURL = "http://";
	if(bUsingSSL) ResultURL = "https://";
	ResultURL += ScriptURL;

	if(RequestType == EWebRequestType::Post) InitRequest(IhttpRequest, "Post", ResultURL);
	else InitRequest(IhttpRequest, "Get", ResultURL);
	TSharedRef<TJsonWriter<>> Json_Writer = TJsonWriterFactory<>::Create(&JsonStream);
	FJsonSerializer::Serialize(JsonRequest.ToSharedRef(), Json_Writer);
	IhttpRequest->SetContentAsString(JsonStream);

	UE_LOG(LogWebRequest, Log, TEXT("Request json data to '%s'." ), ResultURL);
	IhttpRequest->ProcessRequest();
	
	return true;
}

TSharedPtr<FJsonObject> UWebRequestBase::CreateJsonRequest()
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	return JsonObject;
}

void UWebRequestBase::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool WasSuccessful)
{
	if(WasSuccessful)
	{
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(Response->GetContentAsString());

		UE_LOG(LogWebRequest, Log, TEXT("[OnResponseReceived] Response json: \n%s"), *Response->GetContentAsString());

		if(FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			CallJsonResponse(JsonObject);
		}
		else
		{
			UE_LOG(LogWebRequest, Error, TEXT("[OnResponseReceived] Fail to deserialize json!"))
			CallJsonFail();
		}
	}
	else
	{
		CallJsonFail();
	}
}

void UWebRequestBase::InitRequest(TSharedRef<IHttpRequest>& Request, const FString& RequestType, const FString& ScriptURL)
{
	Request->OnProcessRequestComplete().BindUObject(this, &UWebRequestBase::OnResponseReceived);
	Request->SetURL(ScriptURL);
	Request->SetVerb(RequestType);
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	
}
