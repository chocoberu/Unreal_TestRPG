// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestRPG.h"
#include "GameFramework/Character.h"
#include "TBaseEnemyCharacter.generated.h"

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

	// OnHealthChanged() 내부 처리 함수
	virtual void OnHealthChangedProcess(float Health);

	UFUNCTION()
	void OnHealthChanged(class UTHealthComponent* OwningHealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	// Components
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UTHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class AEnemyAIController* EnemyAIController;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	class UWidgetComponent* HPBarWidget;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	class UTestHPBarWidget* HPBarWidgetObject;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player")
	ECharacterAffiliation CharacterAffiliation;

	UPROPERTY(BlueprintReadOnly, Category = "Player")
	bool bDied;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void NormalAttack();

	ECharacterAffiliation GetCharacterAffilation() { return CharacterAffiliation; }
};
