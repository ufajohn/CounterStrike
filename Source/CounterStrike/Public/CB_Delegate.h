// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CB_Delegate.generated.h"

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMyDelegate, int, Param);
/**
 * 
 */
UCLASS(BlueprintType)
class COUNTERSTRIKE_API UCB_Delegate : public UObject
{
	GENERATED_BODY()
	UCB_Delegate() : MyDelegate(FMyDelegate()){}

public:
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable, BlueprintCallable)
	FMyDelegate MyDelegate;	
};
