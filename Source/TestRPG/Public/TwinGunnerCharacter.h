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
	E_ChargeBlast UMETA(DisplayName = "ChargeBlast"),
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
	void QSkill();
	void QSkillReleased();

	UFUNCTION()
	void SpawnUltimateGun();

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

	UPROPERTY(EditAnywhere, Category = "Attack")
	float NormalAttackDamage;

	UPROPERTY(EditAnywhere, Category = "Attack")
	float QSkillAttackDamage;

	bool bQSkillEnd;


private:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack", Meta = (AllowPrivateAccess = true))
	class UParticleSystem* NormalAttackHitParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack", Meta = (AllowPrivateAccess = true))
	class UParticleSystem* NormalAttackNoHitParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack", Meta = (AllowPrivateAccess = true))
	class UParticleSystem* QSkillHitParticle;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack", Meta = (AllowPrivateAccess = true))
	class UParticleSystem* QSkillNoHitParticle;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn", Meta = (AllowPrivateAccess = true))
	bool IsDead;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn", Meta = (AllowPrivateAccess = true))
	bool IsFire;

	FName MuzzleSocket;

	bool SweepAttackCheck(FHitResult& HitResult, FVector& AttackEnd, float SkillRange, float SkillRadius);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void NormalAttackCheck();

	UFUNCTION()
	void QSkillCheck();

	UFUNCTION()
	void SetESkillEnd();

	UFUNCTION()
	void SetQSkillEnd();
};
