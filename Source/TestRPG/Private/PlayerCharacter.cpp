// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "TPlayerAnimInstance.h"
#include "THealthComponent.h"

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

	HealthComponent = CreateDefaultSubobject<UTHealthComponent>(TEXT("HealthComp"));
	HealthComponent->OnHealthChanged.AddUObject(this, &APlayerCharacter::OnHealthChanged);

	bDied = false;
	bNormalAttack = false;
	NormalAttackCoolTime = 1.0f;
	ShiftSkillCoolTime = 1.0f;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void APlayerCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
}

void APlayerCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
}

void APlayerCharacter::OnHealthChanged(UTHealthComponent* OwningHealthComp, float Health, float HealthDelta, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Health <= 0.0f && !bDied)
	{
		bDied = true;

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