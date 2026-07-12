// Copyright Eduard Ciofu

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "B_CombatComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BELTER_API UB_CombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UB_CombatComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	// Cycle to the next weapon in the inventory
	void Initiate_CycleWeapon();
	void Initiate_FireWeapon_Pressed();
	void Initiate_FireWeapon_Released();
	void Initiate_ReloadWeapon();
	void Initiate_AimWeapon_Pressed();
	void Initiate_AimWeapon_Released();
	
protected:


private:

};
