// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Classes/WebRequestBase.h"
#include "WebRequestBaseBP.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDelegateResultTest, const FString&, ValueString, float, ValueFloat);

USTRUCT()
struct FKeyNumber
{
	GENERATED_BODY()
public:
	FKeyNumber() :Key(""), Value(-1.f) {}
	FKeyNumber(const FString &newKey, const float &newValue):Key(newKey), Value(newValue) {}

	UPROPERTY()
	FString Key;
	
	UPROPERTY()
	float Value;	
};

USTRUCT()
struct FKeyString
{
	GENERATED_BODY()
public:
	FKeyString() :Key(""), Value("") {}
	FKeyString(const FString &newKey, const FString &newValue):Key(newKey), Value(newValue) {}

	UPROPERTY()
	FString Key;

	UPROPERTY()
	FString Value;	
};

UCLASS(BlueprintType)
class COUNTERSTRIKE_API UWebRequestBaseBP : public UWebRequestBase
{
	GENERATED_BODY()
protected:
	virtual void CallJsonResponse(const TSharedPtr<FJsonObject>& JsonResponse) override;
	virtual void CallJsonFail() override {};

private:
	TArray<FKeyNumber> Numbers;
	TArray<FKeyString> Strings;

public:
	UPROPERTY(BlueprintAssignable, Category=WebRequest)
	FDelegateResultTest DelegateResultTest;

	UFUNCTION(BlueprintCallable, Category=WebRequest, meta=(DisplayName = "Add Number (BP)"))
	void BP_AddNumber(const FString& Key, float Value){Numbers.Add(FKeyNumber(Key, Value));}

	UFUNCTION(BlueprintCallable, Category=WebRequest, meta=(DisplayName = "Add String (BP)"))
	void BP_AddString(const FString& Key, const FString& Value){Strings.Add(FKeyString(Key, Value));}
	
	UFUNCTION(BlueprintCallable, Category=WebRequest, meta=(DisplayName = "Call Web Script (BP)"))
	void BP_CallScript(const FString& ScriptURL);
};
