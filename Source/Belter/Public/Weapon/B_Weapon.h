// Copyright Eduard Ciofu

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "B_Weapon.generated.h"

UCLASS()
class BELTER_API AB_Weapon : public AActor
{
	GENERATED_BODY()

public:

	AB_Weapon();
	
	virtual void OnRep_Instigator() override;
	
	void AttachToOwningPawn() const;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Belter|Config")
	FGameplayTag WeaponType;
	
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	USkeletalMeshComponent* GetMesh3P() const { return Mesh3P; }
	
protected:

	virtual void BeginPlay() override;

private:
	
	void SetMeshVisibilities(const APawn* OwningPawn) const;
	
	// Weapon Mesh for 1st person view
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> Mesh1P;
	// Weapon Mesh for 3rd person view
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> Mesh3P;
};
