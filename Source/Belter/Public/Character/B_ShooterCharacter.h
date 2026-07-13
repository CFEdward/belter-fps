// Copyright Eduard Ciofu

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/B_PlayerInterface.h"
#include "B_ShooterCharacter.generated.h"

class UInputAction;
class UB_CombatComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class BELTER_API AB_ShooterCharacter : public ACharacter, public IB_PlayerInterface
{
	GENERATED_BODY()

public:

	AB_ShooterCharacter();
	
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	virtual FName GetWeaponAttachPoint_Implementation(const FGameplayTag& WeaponType) const override;

protected:

	
private:
	
	void Input_CycleWeapon();
	void Input_ReloadWeapon();
	void Input_FireWeapon_Pressed();
	void Input_FireWeapon_Released();
	void Input_AimWeapon_Pressed();
	void Input_AimWeapon_Released();
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UB_CombatComponent> CombatComp;
	
	// 1st person view (arms)
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> Mesh1P;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArm;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> FirstPersonCamera;
	
	UPROPERTY(EditAnywhere, Category = "Belter|Input")
	TObjectPtr<UInputAction> CycleWeaponAction;
	UPROPERTY(EditAnywhere, Category = "Belter|Input")
	TObjectPtr<UInputAction> FireWeaponAction;
	UPROPERTY(EditAnywhere, Category = "Belter|Input")
	TObjectPtr<UInputAction> ReloadWeaponAction;
	UPROPERTY(EditAnywhere, Category = "Belter|Input")
	TObjectPtr<UInputAction> AimWeaponAction;
};
