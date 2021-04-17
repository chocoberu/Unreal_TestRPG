// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TwinGunnerUltimateGun.generated.h"

UCLASS()
class TESTRPG_API ATwinGunnerUltimateGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATwinGunnerUltimateGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Components

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USkeletalMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UParticleSystemComponent* LeftShellEjectionComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UParticleSystemComponent* RightShellEjectionComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UParticleSystemComponent* LeftMuzzleComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UParticleSystemComponent* RightMuzzleComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UParticleSystemComponent* LeftShoulderComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UParticleSystemComponent* RightShoulderComp;

	// Particle 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack", Meta = (AllowPrivateAccess = true))
	class UParticleSystem* AttackHitParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack", Meta = (AllowPrivateAccess = true))
	class UParticleSystem* AttackNoHitParticle;
	/*
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack", Meta = (AllowPrivateAccess = true))
	class UParticleSystem* ShellEjectionParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack", Meta = (AllowPrivateAccess = true))
	class UParticleSystem* SholderParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack", Meta = (AllowPrivateAccess = true))
	class UParticleSystem* MuzzleParticle;
	*/

	FTimerHandle UltimateAttackCheckTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack", Meta = (AllowPrivateAccess = true))
	float UltimateAttackCheckTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	float AttackRange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	float AttackRadius;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	float AttackDamage;

	// Particle FName Socket
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	FName LeftShellEjectSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	FName RightShellEjectSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	FName LeftMuzzleSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	FName RightMuzzleSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	FName LeftShoulderSocket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	FName RightShoulderSocket;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void PostInitializeComponents() override;

	void SetWeaponVisible(bool NewFlag);

	void StartUltimaeAttack();

	void EndUltimateAttack();

	UFUNCTION()
	void UltimateAttackCheck();
};
