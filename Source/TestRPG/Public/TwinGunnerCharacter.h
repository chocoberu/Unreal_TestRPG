// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "TwinGunnerCharacter.generated.h"

class ATwinGunnerUltimateGun;
/**
 * 
 */

UENUM(BlueprintType)
enum class ETwinGunnerState : uint8
{
	E_Idle = 0 UMETA(DisplayName = "Idle"),
	E_UltimateGun UMETA(DIsplayName = "UltimateGun"),
	E_Dead UMETA(DisplayName ="Dead"),
};

UCLASS()
class TESTRPG_API ATwinGunnerCharacter : public APlayerCharacter
{
	GENERATED_BODY()
	
public:
	ATwinGunnerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Input Func
	void NormalAttack();
	void Shift();
	void ESkill();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	float AttackRange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	float AttackRadius;

	UPROPERTY()
	ATwinGunnerUltimateGun* UltimateGun;

	UPROPERTY(EditAnywhere, Category = "Player")
	TSubclassOf<ATwinGunnerUltimateGun> UltimateGunClass;

	UPROPERTY(BlueprintReadOnly)
	ETwinGunnerState TwinGunnerPlayerState;

	UPROPERTY(EditAnywhere, Category = "Attack")
	FName UltimateGunSokcet;

private:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack", Meta = (AllowPrivateAccess = true))
	class UParticleSystem* NormalAttackHitParticle;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn", Meta = (AllowPrivateAccess = true))
	bool IsDead;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn", Meta = (AllowPrivateAccess = true))
	bool IsFire;

	FName MuzzleSocket;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void NormalAttackCheck();

	UFUNCTION()
	void SetESkillEnd();
};
