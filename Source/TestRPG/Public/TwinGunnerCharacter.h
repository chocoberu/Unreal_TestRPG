// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "TwinGunnerCharacter.generated.h"

/**
 * 
 */
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	float AttackRange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	float AttackRadius;
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
};
