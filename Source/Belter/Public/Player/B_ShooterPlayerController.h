// Copyright Eduard Ciofu

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "B_ShooterPlayerController.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

UCLASS()
class BELTER_API AB_ShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	
	AB_ShooterPlayerController();
	
protected:
	
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
private:
	
	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);
	void Input_Crouch();
	void Input_Jump();
	
	UPROPERTY(EditAnywhere, Category = "Belter|Input")
	TObjectPtr<UInputMappingContext> ShooterIMC;
	UPROPERTY(EditAnywhere, Category = "Belter|Input")
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, Category = "Belter|Input")
	TObjectPtr<UInputAction> LookAction;
	UPROPERTY(EditAnywhere, Category = "Belter|Input")
	TObjectPtr<UInputAction> CrouchAction;
	UPROPERTY(EditAnywhere, Category = "Belter|Input")
	TObjectPtr<UInputAction> JumpAction;
};
