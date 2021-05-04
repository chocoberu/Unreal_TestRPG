// Fill out your copyright notice in the Description page of Project Settings.


#include "TestSwordBoss.h"
#include "TEnemyAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

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

	if (EnemyAIController != nullptr)
	{
		EnemyAIController->RunAI();
		auto BlackboardComp = EnemyAIController->GetBlackboardComponent();
		if (BlackboardComp == nullptr)
			return;
		BlackboardComp->SetValueAsBool(TEXT("bEntrance"), true);
	}
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
	EnemyAnimInstance->PlayNormalAttackMontage();
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

	if (EnemyAIController != nullptr)
	{
		auto BlackboardComp = EnemyAIController->GetBlackboardComponent();
		if (BlackboardComp == nullptr)
			return;
		BlackboardComp->SetValueAsBool(TEXT("bEntrance"), false);
	}
}

void ATestSwordBoss::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}