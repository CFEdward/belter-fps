// Copyright Eduard Ciofu

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "B_WeaponData.generated.h"

class UBlendSpace;
class UAnimSequence;

USTRUCT(BlueprintType)
struct FB_PlayerAnims
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimSequence> IdleAnim{ nullptr };
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimSequence> AimIdleAnim{ nullptr };
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimSequence> CrouchIdleAnim{ nullptr };
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimSequence> SprintAnim{ nullptr };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBlendSpace> AimOffset_Hip;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBlendSpace> AimOffset_Aim;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBlendSpace> Strafe_Standing;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBlendSpace> Strafe_Crouching;
};

UCLASS()
class BELTER_API UB_WeaponData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditDefaultsOnly, Category = "Belter|Attachment Settings")
	TMap<FGameplayTag, FName> GripSockets;
	UPROPERTY(EditDefaultsOnly, Category = "Belter|Attachment Settings")
	TMap<FGameplayTag, FName> LeftHandFABRIKSockets;
	UPROPERTY(EditDefaultsOnly, Category = "Belter|Attachment Settings")
	FName RightHandBone;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Belter|Animation|FirstPerson")
	TMap<FGameplayTag, FB_PlayerAnims> FirstPersonAnims;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Belter|Animation|ThirdPerson")
	TMap<FGameplayTag, FB_PlayerAnims> ThirdPersonAnims;
};
