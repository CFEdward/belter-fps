// Copyright Eduard Ciofu

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "B_CombatComponent.generated.h"

class AB_Weapon;
class UB_WeaponData;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BELTER_API UB_CombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UB_CombatComponent();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void SpawnInventory();
	void Equip(AB_Weapon* Weapon);
	void DestroyInventory();
	
	// Cycle to the next weapon in the inventory
	void Initiate_CycleWeapon();
	void Initiate_FireWeapon_Pressed();
	void Initiate_FireWeapon_Released();
	void Initiate_ReloadWeapon();
	void Initiate_AimWeapon_Pressed();
	void Initiate_AimWeapon_Released();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Belter|Weapon")
	TObjectPtr<UB_WeaponData> WeaponData;
	
protected:

	UPROPERTY(Transient, BlueprintReadOnly, ReplicatedUsing = OnRep_CurrentWeapon)
	TObjectPtr<AB_Weapon> CurrentWeapon;

private:
	
	UFUNCTION()
	void OnRep_CurrentWeapon(AB_Weapon* LastWeapon);
	
	AB_Weapon* SpawnWeapon(TSubclassOf<AB_Weapon> WeaponClass) const;

	UPROPERTY(Transient, Replicated)
	TArray<TObjectPtr<AB_Weapon>> Inventory;
	
	UPROPERTY(EditDefaultsOnly, Category = "Belter|Weapon")
	TArray<TSubclassOf<AB_Weapon>> DefaultWeaponClasses;
};
