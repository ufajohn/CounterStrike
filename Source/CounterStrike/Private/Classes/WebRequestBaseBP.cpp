// Fill out your copyright notice in the Description page of Project Settings.


#include "Classes/WebRequestBaseBP.h"

void UWebRequestBaseBP::CallJsonResponse(const TSharedPtr<FJsonObject>& JsonResponse)
{
	//Super::CallJsonResponse(JsonResponse);
	FString ResultString = "";
	double ResultNumber = 0.f;

	if(!JsonResponse->HasField("ResultText")) return;
	ResultNumber = JsonResponse->GetNumberField("resultNumber");
	ResultString = JsonResponse->GetStringField("resultText");
	float ResultFloat = (float)ResultNumber;
	UE_LOG(LogTemp, Warning, TEXT("Web response: string = '%s', number = '%f'."), *ResultString, ResultFloat);
	DelegateResultTest.Broadcast(ResultString, ResultFloat);
}

void UWebRequestBaseBP::BP_CallScript(const FString& ScriptURL)
{
	TSharedPtr<FJsonObject> Json = CreateJsonRequest();
	if(Numbers.Num() > 0)
	{
		for (const FKeyNumber& Number : Numbers)
		{
			Json->SetNumberField(Number.Key, Number.Value);
		}
	}

	if (Strings.Num() > 0)
	{
		for (const FKeyString& String : Strings)
		{
			Json->SetStringField(String.Key, String.Value);
		}
	}

	CallWebScript(ScriptURL, Json);
}
