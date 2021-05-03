// Fill out your copyright notice in the Description page of Project Settings.


#include "TestSwordBoss.h"
#include "TEnemyAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

ATestSwordBoss::ATestSwordBoss()
{
	bEntrance = true;
}

void ATestSwordBoss::BeginPlay()
{
	Super::BeginPlay();
	EnemyAnimInstance = Cast<UTEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	EnemyAnimInstance->OnEntranceStartDelegate.AddUObject(this, &ATestSwordBoss::SetEntranceStart);
	EnemyAnimInstance->OnEntranceEndDelegate.AddUObject(this, &ATestSwordBoss::SetEntranceEnd);
}

void ATestSwordBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 테스트 코드
	if(bEntrance)
		MoveForward(1.0f);
}

void ATestSwordBoss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATestSwordBoss::NormalAttack()
{
	
}

void ATestSwordBoss::SetEntranceStart()
{
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;
	bEntrance = true;
}

void ATestSwordBoss::SetEntranceEnd()
{
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	bEntrance = false;
}

void ATestSwordBoss::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}