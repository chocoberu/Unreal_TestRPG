// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordEnemyCharacter.h"
#include "TEnemyAnimInstance.h"
#include "TWeapon.h"

ASwordEnemyCharacter::ASwordEnemyCharacter()
{
	RightWeaponAttachSocketName = "hand_rWeaponSocket";
}

void ASwordEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	EnemyAnimInstance = Cast<UTEnemyAnimInstance>(GetMesh()->GetAnimInstance());

	// Spawn a default weapon
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	CurrentWeapon = GetWorld()->SpawnActor<ATWeapon>(WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	if (CurrentWeapon)
	{
		CurrentWeapon->SetOwner(this);
		CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, RightWeaponAttachSocketName);
	}
}

void ASwordEnemyCharacter::PlayHitMontage()
{
	Super::PlayHitMontage();
	EnemyAnimInstance->PlayHitMontage();
}

void ASwordEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASwordEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
