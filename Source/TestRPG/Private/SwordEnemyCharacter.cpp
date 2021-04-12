// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordEnemyCharacter.h"
#include "TEnemyAnimInstance.h"

ASwordEnemyCharacter::ASwordEnemyCharacter()
{
	
}

void ASwordEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	EnemyAnimInstance = Cast<UTEnemyAnimInstance>(GetMesh()->GetAnimInstance());
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
