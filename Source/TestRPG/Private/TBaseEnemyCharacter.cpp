// Fill out your copyright notice in the Description page of Project Settings.


#include "TBaseEnemyCharacter.h"
#include "THealthComponent.h"
#include "TEnemyAnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnemyAIController.h"
#include "Components/WidgetComponent.h"
#include "TestHPBarWidget.h"
#include "Widget/DamageTextWidget.h"

// Sets default values
ATBaseEnemyCharacter::ATBaseEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UTHealthComponent>(TEXT("HealthComp"));
	HealthComponent->OnHealthChanged.AddUObject(this, &ATBaseEnemyCharacter::OnHealthChanged);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("TestRPGCharacter"));

	CharacterAffiliation = ECharacterAffiliation::E_Enemy;

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

void ATBaseEnemyCharacter::OnHealthChangedProcess(float Health, float Damage)
{
	if (HPBarWidgetObject != nullptr)
	{
		HPBarWidgetObject->UpdateHPWidget();

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		//auto DamageText = GetWorld()->SpawnActor<UDamageTextWidget>(DamageTextClass, GetActorLocation(), GetActorRotation(), SpawnParams);
		
		//auto DamageText = CreateWidget<UDamageTextWidget>(EnemyAIController, DamageTextClass);
		//
		//if (DamageText != nullptr)
		//{
		//	DamageText->AddToPlayerScreen();
		//	//DamageText
		//	FText DamageTextValue = FText::FromString(FString::SanitizeFloat(Damage));
		//	DamageText->UpdateDamage(DamageTextValue);
		//}
	}
	if (Health > 0.0f)
	{
		PlayHitMontage();
	}
}

void ATBaseEnemyCharacter::OnHealthChanged(UTHealthComponent* OwningHealthComp, float Health, float HealthDelta, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	OnHealthChangedProcess(Health, HealthDelta);

	// Enemy Character 죽었을 때 처리
	if (Health <= 0.0f && !bDied)
	{
		bDied = true;

		GetMovementComponent()->StopMovementImmediately();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		auto AnimInst = Cast<UTEnemyAnimInstance>(GetMesh()->GetAnimInstance());
		AnimInst->SetDeadAnim();

		EnemyAIController->StopAI();
		
		DetachFromControllerPendingDestroy();

		HPBarWidget->SetHiddenInGame(true);
		
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
	//UE_LOG(LogTemp, Log, TEXT("TODO : Enemy Normal Attack"));
	bNormalAttack = true;
}


void ATBaseEnemyCharacter::OnAttackEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (bNormalAttack)
		bNormalAttack = false;

	OnAttackEnd.Broadcast();
}
