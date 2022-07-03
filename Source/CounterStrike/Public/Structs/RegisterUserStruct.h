// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RegisterUserStruct.generated.h"


USTRUCT(BlueprintType)
struct FRegisterUserData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Login;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Password;
	
};

