// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TBaseEnemyCharacter.generated.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	E_Idle = 0 UMETA(DisplayName = "Idle"),
	E_Patrol UMETA(DisplayName = "Patrol"),
	E_Chasing UMETA(DIsplayName = "Chasing"),
	E_Dead UMETA(DisplayName = "Dead"),
};

UCLASS()
class TESTRPG_API ATBaseEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATBaseEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PlayHitMontage();

	UFUNCTION()
	void OnHealthChanged(class UTHealthComponent* OwningHealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	// Components
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UTHealthComponent* HealthComponent;

	/*UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UAIPerceptionComponent* AIPerceptionComponent;*/

	UPROPERTY(BlueprintReadOnly, Category = "Player")
	bool bDied;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void NormalAttack();
};
