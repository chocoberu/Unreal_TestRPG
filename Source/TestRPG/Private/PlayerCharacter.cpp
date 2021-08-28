// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Blueprint/UserWidget.h"
#include "TPlayerAnimInstance.h"
#include "THealthComponent.h"
#include "Components/WidgetComponent.h"
#include "TestHPBarWidget.h"
#include "Widget/BloodOverlayHUDWidget.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Camera Component
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->TargetArmLength = 300.0f;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("TestRPGCharacter"));

	HealthComponent = CreateDefaultSubobject<UTHealthComponent>(TEXT("HealthComp"));
	HealthComponent->OnHealthChanged.AddUObject(this, &APlayerCharacter::OnHealthChanged);

	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarWidget"));
	HPBarWidget->SetupAttachment(GetMesh());

	CharacterAffiliation = ECharacterAffiliation::E_Player;

	bDied = false;
	bNormalAttack = false;
	NormalAttackCoolTime = 1.0f;
	ShiftSkillCoolTime = 1.0f;

	PrevMoveState = EPrevMoveState::E_None;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	HPBarWidgetObject = Cast<UTestHPBarWidget>(HPBarWidget->GetUserWidgetObject());
	if (HPBarWidgetObject != nullptr)
	{
		HPBarWidgetObject->BindCharacter(HealthComponent);
	}

	BloodOverlayHUD = Cast<UBloodOverlayHUDWidget>(CreateWidget(GetWorld(), BloodOverlayHUDClass));
	if (BloodOverlayHUD != nullptr)
	{
		BloodOverlayHUD->AddToViewport();
	}
}

void APlayerCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
	if (Value > 0.0f)
		PrevMoveState = EPrevMoveState::E_W;
	else if (Value < 0.0f)
		PrevMoveState = EPrevMoveState::E_S;
	
}

void APlayerCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
	if (Value > 0.0f)
		PrevMoveState = EPrevMoveState::E_D;
	else if (Value < 0.0f)
		PrevMoveState = EPrevMoveState::E_A;
}

void APlayerCharacter::OnHealthChanged(UTHealthComponent* OwningHealthComp, float Health, float HealthDelta, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (HPBarWidgetObject != nullptr)
	{
		HPBarWidgetObject->UpdateHPWidget();
		if(HealthDelta > 0.0f)
			BloodOverlayHUD->UpdateHUDWidget(HealthComponent->GetHPRatio());
	}
	if (Health <= 0.0f && !bDied)
	{
		bDied = true;

		SetWeaponVisible(false);
		
		GetMovementComponent()->StopMovementImmediately();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		auto AnimInst = Cast<UTPlayerAnimInstance>(GetMesh()->GetAnimInstance());
		AnimInst->SetDeadAnim();

		DetachFromControllerPendingDestroy();
		GetWorldTimerManager().ClearTimer(NormalAttackTimer);

		SetLifeSpan(10.0f);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACharacter::Jump);
}

void APlayerCharacter::SetNormalAttackEnd()
{
	bNormalAttack = false;
}

void APlayerCharacter::SetShiftSkillEnd()
{
	bShift = false;
}

void APlayerCharacter::SetQSkillEnd()
{
	bQSkill = false;
}

void APlayerCharacter::SetESkillEnd()
{
	bESkill = false;
}

float APlayerCharacter::GetHealth() const
{
	return HealthComponent->GetHealth();
}

void APlayerCharacter::SetWeaponVisible(bool NewFlag)
{

}
