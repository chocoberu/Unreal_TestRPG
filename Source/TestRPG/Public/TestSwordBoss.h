// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TBaseEnemyCharacter.h"
#include "TestSwordBoss.generated.h"

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

	// Components
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UTEnemyAnimInstance* EnemyAnimInstance;

	bool bEntrance;
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
};

