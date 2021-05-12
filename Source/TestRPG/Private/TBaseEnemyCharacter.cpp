// Fill out your copyright notice in the Description page of Project Settings.


#include "TBaseEnemyCharacter.h"
#include "THealthComponent.h"
#include "TEnemyAnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnemyAIController.h"
#include "Components/WidgetComponent.h"
#include "TestHPBarWidget.h"

// Sets default values
ATBaseEnemyCharacter::ATBaseEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UTHealthComponent>(TEXT("HealthComp"));
	HealthComponent->OnHealthChanged.AddUObject(this, &ATBaseEnemyCharacter::OnHealthChanged);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("TestRPGCharacter"));

	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarWidget"));
	HPBarWidget->SetupAttachment(GetMesh());
	
}

// Called when the game starts or when spawned
void ATBaseEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();	
	EnemyAIController = Cast<AEnemyAIController>(GetController());

	HPBarWidgetObject = Cast<UTestHPBarWidget>(HPBarWidget->GetUserWidgetObject());
	if (HPBarWidgetObject != nullptr)
	{
		HPBarWidgetObject->BindCharacter(HealthComponent);
	}
}

void ATBaseEnemyCharacter::PlayHitMontage()
{

}

void ATBaseEnemyCharacter::OnHealthChanged(UTHealthComponent* OwningHealthComp, float Health, float HealthDelta, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (HPBarWidgetObject != nullptr)
	{
		HPBarWidgetObject->UpdateHPWidget();
	}
	if (Health > 0.0f)
	{
		PlayHitMontage();
		return;
	}

	if (Health <= 0.0f && !bDied)
	{
		bDied = true;

		GetMovementComponent()->StopMovementImmediately();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		auto AnimInst = Cast<UTEnemyAnimInstance>(GetMesh()->GetAnimInstance());
		AnimInst->SetDeadAnim();

		EnemyAIController->StopAI();
		
		DetachFromControllerPendingDestroy();
		
		SetLifeSpan(10.0f);
	}
}

// Called every frame
void ATBaseEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATBaseEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATBaseEnemyCharacter::NormalAttack()
{
	UE_LOG(LogTemp, Log, TEXT("TODO : Enemy Normal Attack"));
}

