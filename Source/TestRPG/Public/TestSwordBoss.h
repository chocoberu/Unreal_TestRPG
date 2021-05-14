// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestRPG.h"
#include "TBaseEnemyCharacter.h"
#include "TestSwordBoss.generated.h"

class ATBaseEnemyCharacter;
/**
 * 
 */
UCLASS()
class TESTRPG_API ATestSwordBoss : public ATBaseEnemyCharacter
{
	GENERATED_BODY()

public:
	ATestSwordBoss();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool SweepAttackCheck(FHitResult& HitResult, FVector& AttackEnd, float SkillRange, float SkillRadius);

	// Components
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UTEnemyAnimInstance* EnemyAnimInstance;

	bool bEntrance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	float AttackRange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	float AttackRadius;

	UPROPERTY(EditAnywhere, Category = "Attack")
	float NormalAttackDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character")
	float DefaultMaxSpeed;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<ATBaseEnemyCharacter> MinionClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	float SpawnCoolTime;

	FTimerHandle SpawnTimer;

	UPROPERTY(BlueprintReadOnly, Category = "Attack")
	bool bSpawnMinion;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void NormalAttack();

	void MoveForward(float Value);

	UFUNCTION()
	void SetEntranceStart();

	UFUNCTION()
	void SetEntranceEnd();

	UFUNCTION()
	void NormalAttackCheck();

	void SpawnMinion();
};

