// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UTPlayerAnimInstance;

UCLASS()
class TESTRPG_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Input Func
	void MoveForward(float Value);
	void MoveRight(float Value);

	UFUNCTION()
	void OnHealthChanged(class UTHealthComponent* OwningHealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
	
	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USpringArmComponent* SpringArmComp;

	// Components
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UTPlayerAnimInstance* AnimInstance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UTHealthComponent* HealthComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Player")
	bool bDied;

	UPROPERTY(BlueprintReadOnly, Category = "Attack")
	bool bNormalAttack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	float NormalAttackCoolTime;

	FTimerHandle NormalAttackTimer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
