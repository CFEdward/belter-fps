// Copyright Eduard Ciofu

#include "Combat/B_CombatComponent.h"

UB_CombatComponent::UB_CombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UB_CombatComponent::TickComponent(const float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UB_CombatComponent::Initiate_CycleWeapon()
{
}

void UB_CombatComponent::Initiate_FireWeapon_Pressed()
{
}

void UB_CombatComponent::Initiate_FireWeapon_Released()
{
}

void UB_CombatComponent::Initiate_ReloadWeapon()
{
}

void UB_CombatComponent::Initiate_Aim_Pressed()
{
}

void UB_CombatComponent::Initiate_Aim_Released()
{
}
