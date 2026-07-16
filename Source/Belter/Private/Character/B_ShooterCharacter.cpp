// Copyright Eduard Ciofu

#include "Character/B_ShooterCharacter.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Combat/B_CombatComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Data/B_WeaponData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Weapon/B_Weapon.h"

AB_ShooterCharacter::AB_ShooterCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetCharacterMovement()->MovementState.bCanCrouch = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 0.f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 15.f;
	SpringArm->bUsePawnControlRotation = true;
	
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>("FirstPersonCamera");
	FirstPersonCamera->SetupAttachment(SpringArm);
	FirstPersonCamera->bUsePawnControlRotation = false;
	
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh1P");
	Mesh1P->SetupAttachment(FirstPersonCamera);
	Mesh1P->bOnlyOwnerSee = true;
	Mesh1P->bOwnerNoSee = false;
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->bReceivesDecals = false;
	Mesh1P->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
	Mesh1P->PrimaryComponentTick.TickGroup = TG_PrePhysics;
	
	GetMesh()->bOnlyOwnerSee = false;
	GetMesh()->bOwnerNoSee = true;
	GetMesh()->bReceivesDecals = false;
	
	CombatComp = CreateDefaultSubobject<UB_CombatComponent>("Combat");
	CombatComp->SetIsReplicated(true);
}

void AB_ShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	FirstPersonCamera->SetFieldOfView(DefaultFOV);
	StartingAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
}

void AB_ShooterCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (!IsValid(CombatComp)) return;
	
	CombatComp->SpawnInventory();
}

void AB_ShooterCharacter::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CalculateTurnInPlaceParams(DeltaTime);
	CalculateFABRIKSocketTransform();
}

void AB_ShooterCharacter::CalculateFABRIKSocketTransform()
{
	if (!IsValid(CombatComp) || !IsValid(CombatComp->GetCurrentWeapon()) || !IsValid(CombatComp->WeaponData) || !IsValid(CombatComp->GetCurrentWeapon()->GetMesh3P())) return;
	
	FABRIK_SocketTransform = CombatComp->GetCurrentWeapon()->GetMesh3P()->GetSocketTransform(
		*CombatComp->WeaponData->LeftHandFABRIKSockets.Find(CombatComp->GetCurrentWeapon()->WeaponType),
		RTS_World
	);
	FVector OutLocation;
	FRotator OutRotation;
	GetMesh()->TransformToBoneSpace(
		CombatComp->WeaponData->RightHandBone,
		FABRIK_SocketTransform.GetLocation(),
		FABRIK_SocketTransform.GetRotation().Rotator(),
		OutLocation,
		OutRotation
	);
	FABRIK_SocketTransform.SetLocation(OutLocation);
	FABRIK_SocketTransform.SetRotation(OutRotation.Quaternion());
}

void AB_ShooterCharacter::CalculateTurnInPlaceParams(const float DeltaTime)
{
	const FVector Velocity = GetVelocity();
	const float Speed = Velocity.Size2D();
	const bool bIsInAir = GetCharacterMovement()->IsFalling();
	
	// Standing still, not jumping
	if (Speed == 0.f && !bIsInAir)
	{
		const FRotator CurrentAimRotation(0.f, GetBaseAimRotation().Yaw, 0.f);
		// StartingAimRotation initially set in BeginPlay
		const FRotator DeltaAimRotation = UKismetMathLibrary::NormalizedDeltaRotator(CurrentAimRotation, StartingAimRotation);
		AO_Yaw = DeltaAimRotation.Yaw;
		
		if (TurningStatus == EB_TurningInPlace::NotTurning)
		{
			InterpAO_Yaw = AO_Yaw;
		}
		
		TurnInPlace(DeltaTime);
	}
	
	if (Speed > 0.f || bIsInAir)
	{
		StartingAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
		AO_Yaw = 0.f;

		const FRotator AimRotation = GetBaseAimRotation();
		const FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(Velocity);
		MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;
		TurningStatus = EB_TurningInPlace::NotTurning;
	}
	
	AO_Yaw *= -1.f;
}

void AB_ShooterCharacter::TurnInPlace(const float DeltaTime)
{
	if (AO_Yaw > 90.f)
	{
		TurningStatus = EB_TurningInPlace::Right;
	}
	else if (AO_Yaw < -90.f)
	{
		TurningStatus = EB_TurningInPlace::Left;
	}
	if (TurningStatus != EB_TurningInPlace::NotTurning)
	{
		InterpAO_Yaw = FMath::FInterpTo(InterpAO_Yaw, 0.f, DeltaTime, 4.f);
		AO_Yaw = InterpAO_Yaw;
		if (FMath::Abs(AO_Yaw) < 5.f)
		{
			TurningStatus = EB_TurningInPlace::NotTurning;
			StartingAimRotation = FRotator(0.f, GetBaseAimRotation().Yaw, 0.f);
		}
	}
}

void AB_ShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* ShooterInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	ShooterInputComponent->BindAction(CycleWeaponAction, ETriggerEvent::Started, this, &ThisClass::Input_CycleWeapon);
	ShooterInputComponent->BindAction(ReloadWeaponAction, ETriggerEvent::Started, this, &ThisClass::Input_ReloadWeapon);
	ShooterInputComponent->BindAction(FireWeaponAction, ETriggerEvent::Started, this, &ThisClass::Input_FireWeapon_Pressed);
	ShooterInputComponent->BindAction(FireWeaponAction, ETriggerEvent::Completed, this, &ThisClass::Input_FireWeapon_Released);
	ShooterInputComponent->BindAction(AimWeaponAction, ETriggerEvent::Started, this, &ThisClass::Input_AimWeapon_Pressed);
	ShooterInputComponent->BindAction(AimWeaponAction, ETriggerEvent::Completed, this, &ThisClass::Input_AimWeapon_Released);
}

void AB_ShooterCharacter::BeginDestroy()
{
	Super::BeginDestroy();
	if (!IsValid(CombatComp)) return;
	
	CombatComp->DestroyInventory();
}

#pragma region InputCallbacks
void AB_ShooterCharacter::Input_CycleWeapon()
{
	CombatComp->Initiate_CycleWeapon();
}

void AB_ShooterCharacter::Input_ReloadWeapon()
{
	CombatComp->Initiate_ReloadWeapon();
}

void AB_ShooterCharacter::Input_FireWeapon_Pressed()
{
	CombatComp->Initiate_FireWeapon_Pressed();
}

void AB_ShooterCharacter::Input_FireWeapon_Released()
{
	CombatComp->Initiate_FireWeapon_Released();
}

void AB_ShooterCharacter::Input_AimWeapon_Pressed()
{
	CombatComp->Initiate_AimWeapon_Pressed();
	OnAim(true);
}

void AB_ShooterCharacter::Input_AimWeapon_Released()
{
	CombatComp->Initiate_AimWeapon_Released();
	OnAim(false);
}
#pragma endregion

FName AB_ShooterCharacter::GetWeaponAttachPoint_Implementation(const FGameplayTag& WeaponType) const
{
	checkf(CombatComp->WeaponData, TEXT("No Weapon Data Asset - PLease fill out BP_ShooterCharacter"));
	return CombatComp->WeaponData->GripSockets.FindChecked(WeaponType);
}

bool AB_ShooterCharacter::HasCurrentWeapon() const
{
	return IsValid(CombatComp) && CombatComp->GetCurrentWeapon() != nullptr;
}

FRotator AB_ShooterCharacter::GetFixedAimRotation() const
{
	FRotator AimRotation = GetBaseAimRotation();
	if (AimRotation.Pitch > 90.f && !IsLocallyControlled())
	{
		// Map pitch from [270, 360) to [-90, 0]
		const FVector2D InRange(270.f, 360.f);
		const FVector2D OutRange(-90.f, 0.f);
		AimRotation.Pitch = FMath::GetMappedRangeValueClamped(InRange, OutRange, AimRotation.Pitch);
	}
	
	return AimRotation;
}

