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
