#pragma once

#include "CoreMinimal.h"
#include "Structs/ServerPrivatInfoStruct.h"
//#include "UObject/NoExportTypes.h"
#include "Cb_RequestGetServerInfoFromDB.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FDelegateCallbackRequestGetServerInfoFromDB, const FServerPrivateInfo&, Info);

USTRUCT()
struct FCallbackRequestGetServerInfoFromDB
{
	GENERATED_BODY()

	FCallbackRequestGetServerInfoFromDB(): DelegateCallbackRequestGetServerInfoFromDB(FDelegateCallbackRequestGetServerInfoFromDB()){}

	FCallbackRequestGetServerInfoFromDB(const FDelegateCallbackRequestGetServerInfoFromDB& Callback): DelegateCallbackRequestGetServerInfoFromDB(Callback){}

	UPROPERTY()
	FDelegateCallbackRequestGetServerInfoFromDB DelegateCallbackRequestGetServerInfoFromDB;
};

/**
 * 
 */
UCLASS()
class COUNTERSTRIKE_API UCb_RequestGetServerInfoFromDB : public UObject
{
	GENERATED_BODY()
	
};
