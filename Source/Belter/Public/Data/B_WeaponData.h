// Copyright Eduard Ciofu

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "B_WeaponData.generated.h"

UCLASS()
class BELTER_API UB_WeaponData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditDefaultsOnly, Category = "Belter|WeaponData|Config")
	TMap<FGameplayTag, FName> GripPoints;
};
