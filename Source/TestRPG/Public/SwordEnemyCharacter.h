// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TBaseEnemyCharacter.h"
#include "SwordEnemyCharacter.generated.h"

class ATWeapon;
/**
 * 
 */
UCLASS()
class TESTRPG_API ASwordEnemyCharacter : public ATBaseEnemyCharacter
{
	GENERATED_BODY()

public:

	ASwordEnemyCharacter();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PlayHitMontage();

	// Components
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UTEnemyAnimInstance* EnemyAnimInstance;

	// Weapon
	UPROPERTY()
	ATWeapon* CurrentWeapon;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<ATWeapon> WeaponClass;

	UPROPERTY(EditAnywhere, Category = "Player")
	FName RightWeaponAttachSocketName;

	UPROPERTY(EditAnywhere, Category = "Attack")
	float AttackDamage;

	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void NormalAttack() override;

	UFUNCTION()
	void NormalAttackCheck();
};
