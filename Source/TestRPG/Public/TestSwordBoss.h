// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestRPG.h"
#include "TBaseEnemyCharacter.h"
#include "TestSwordBoss.generated.h"

class ATBaseEnemyCharacter;
class ATestSlash;
/**
 * 
 */

UENUM(BlueprintType)
enum class EBossPhase : uint8
{
	E_Phase1 = 0 UMETA(DisplayName = "Phase1"),
	E_Phase2 UMETA(DisplayName = "Phase2"),
};


UCLASS()
class TESTRPG_API ATestSwordBoss : public ATBaseEnemyCharacter
{
	GENERATED_BODY()

public:
	ATestSwordBoss();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnHealthChangedProcess(float Health) override;

	bool SweepMultiAttackCheck(TArray<FHitResult>& OutHits, FVector& AttackEnd, float SkillRange, float SkillRadius);

	bool SweepAttackCheck(FHitResult& HitResult, FVector& AttackEnd, float SkillRange, float SkillRadius);

	// Components
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UTEnemyAnimInstance* EnemyAnimInstance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UBlackboardComponent* BlackboardComp;

	bool bEntrance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	float AttackRange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	float AttackRadius;

	UPROPERTY(EditAnywhere, Category = "Attack")
	float NormalAttackDamage;

	UPROPERTY(EditAnywhere, Category = "Attack")
	float UppercutAttackDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character")
	float DefaultMaxSpeed;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<ATBaseEnemyCharacter> MinionClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	float SpawnCoolTime;

	FTimerHandle SpawnTimer;

	UPROPERTY(BlueprintReadOnly, Category = "Attack")
	bool bSpawnMinion;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<ATestSlash> SlashClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	float UppercutCoolTime;

	FTimerHandle UppercutTimer;

	UPROPERTY(BlueprintReadOnly, Category = "Attack")
	bool bUppercut;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	EBossPhase BossPhase;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	float Phase2Percent;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void NormalAttack();

	void UppercutAttack();

	void MoveForward(float Value);

	UFUNCTION()
	void SetEntranceStart();

	UFUNCTION()
	void SetEntranceEnd();

	UFUNCTION()
	void NormalAttackCheck();

	UFUNCTION()
	void UppercutAttackCheck();

	UFUNCTION()
	void RotateToTarget();

	void SpawnMinion();

	bool CanUppercut();

	bool CanSpawn();

};

