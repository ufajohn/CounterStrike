#include "Components/PlayerController/AC_DatabaseTransfer.h"
#include "Classes/WebRequests/WebRequestRegisterUser.h"


UAC_DatabaseTransfer::UAC_DatabaseTransfer()
{
	PrimaryComponentTick.bCanEverTick = false;
	RegisterUserURL = "greenstrike.ru/phpscripts/RegisterUser.php";
}

void UAC_DatabaseTransfer::RegisterUser(const FRegisterUserData& RegisterUserData, const FDelegateCallbackRequestRegisterUser& Callback)
{
	//todo сделать проверки на данные пользователя при регистрации
	CallbackRequestRegisterUser.DelegateCallbackRequestRegisterUser = Callback;

	FDelegateCallbackRequestRegisterUser DelegateCallbackRequestRegisterUser;
	DelegateCallbackRequestRegisterUser.BindUFunction(this, "WebResponseRegisterUser");
	
	UWebRequestRegisterUser* Obj = UWebRequestRegisterUser::Create(GetOwner(), RegisterUserURL, RegisterUserData, DelegateCallbackRequestRegisterUser);
	if(!Obj)
	{
		UE_LOG(LogTemp, Error, TEXT("Fail to create object 'UWebRequestRegisterUser'!"));
        		CallbackRequestRegisterUser.DelegateCallbackRequestRegisterUser.ExecuteIfBound(false, TArray<FServersInfo>());
	}
	
}

void UAC_DatabaseTransfer::WebResponseRegisterUser(bool Success, const TArray<FServersInfo>& ServersInfo)
{
	bool Result = CallbackRequestRegisterUser.DelegateCallbackRequestRegisterUser.ExecuteIfBound(Success, ServersInfo);
}

