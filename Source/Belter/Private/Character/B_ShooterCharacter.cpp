// Copyright Eduard Ciofu

#include "Character/B_ShooterCharacter.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Combat/B_CombatComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

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
	
}

void AB_ShooterCharacter::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

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
}

void AB_ShooterCharacter::Input_AimWeapon_Released()
{
	CombatComp->Initiate_AimWeapon_Released();
}
