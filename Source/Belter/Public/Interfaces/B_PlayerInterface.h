// Copyright Eduard Ciofu

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "B_PlayerInterface.generated.h"

struct FGameplayTag;

// This class does not need to be modified.
UINTERFACE()
class UB_PlayerInterface : public UInterface
{
	GENERATED_BODY()
};

class BELTER_API IB_PlayerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	USkeletalMeshComponent* GetMesh1P() const;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	USkeletalMeshComponent* GetMesh3P() const;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FName GetWeaponAttachPoint(const FGameplayTag& WeaponType) const;
};
