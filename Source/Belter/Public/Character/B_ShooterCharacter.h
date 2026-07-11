// Copyright Eduard Ciofu

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "B_ShooterCharacter.generated.h"

class UB_CombatComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class BELTER_API AB_ShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AB_ShooterCharacter();
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:

	
private:	
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UB_CombatComponent> CombatComp;
	
	// 1st person view (arms)
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> Mesh1P;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArm;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> FirstPersonCamera;
};
