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
	
protected:


private:

};
