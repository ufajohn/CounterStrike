// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Classes/WebRequestBase.h"
#include "Classes/Callbacks/CB_RegisterUser.h"
#include "Structs/RegisterUserStruct.h"
#include "UObject/NoExportTypes.h"
#include "WebRequestRegisterUser.generated.h"

/**
 * 
 */
UCLASS()
class COUNTERSTRIKE_API UWebRequestRegisterUser : public UWebRequestBase
{
	GENERATED_BODY()
public:

	static  UWebRequestRegisterUser* Create(UObject* Owner, const FString& ScriptURL, const FRegisterUserData& Data, const FDelegateCallbackRequestRegisterUser& Callback);

	protected:
		virtual void CallJsonResponse(const TSharedPtr<FJsonObject>& JsonResponse) override;
		virtual void CallJsonFail() override;

	private:
		void Init(const FString& ScriptURL, const FRegisterUserData& Data, const FDelegateCallbackRequestRegisterUser& Callback);
		FCallbackRequestRegisterUser CallbackRequestRegisterUser;

	
};
