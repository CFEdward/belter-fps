// Copyright Eduard Ciofu

#include "Combat/B_CombatComponent.h"

#include "Engine/Engine.h"

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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Initiate_CycleWeapon"), false);
}

void UB_CombatComponent::Initiate_FireWeapon_Pressed()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Initiate_FireWeapon_Pressed"), false);
}

void UB_CombatComponent::Initiate_FireWeapon_Released()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Initiate_FireWeapon_Released"), false);
}

void UB_CombatComponent::Initiate_ReloadWeapon()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Initiate_ReloadWeapon"), false);
}

void UB_CombatComponent::Initiate_AimWeapon_Pressed()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Initiate_AimWeapon_Pressed"), false);
}

void UB_CombatComponent::Initiate_AimWeapon_Released()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Initiate_AimWeapon_Released"), false);
}
