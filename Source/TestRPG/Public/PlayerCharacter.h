// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestRPG.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UENUM(BlueprintType)
enum class EPrevMoveState : uint8
{
	E_W = 0 UMETA(DisplayName = "W"),
	E_S UMETA(DisplayName = "S"),
	E_A UMETA(DisplayName = "A"),
	E_D UMETA(DisplayName = "D"),
	E_None UMETA(DisplayName = "None"),
};

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

	// UI
	UPROPERTY(VisibleAnywhere, Category = "UI")
	class UWidgetComponent* HPBarWidget;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	class UTestHPBarWidget* HPBarWidgetObject;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player")
	ECharacterAffiliation CharacterAffiliation;

	UPROPERTY(BlueprintReadOnly, Category = "Player")
	bool bDied;

	UPROPERTY(BlueprintReadOnly, Category = "Attack")
	bool bNormalAttack;

	UPROPERTY(BlueprintReadOnly, Category = "Attack")
	bool bShift;

	UPROPERTY(BlueprintReadOnly, Category = "Attack")
	bool bQSkill;

	UPROPERTY(BlueprintReadOnly, Category = "Attack")
	bool bESkill;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	float NormalAttackCoolTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	float ShiftSkillCoolTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	float QSkillCoolTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	float ESkillCoolTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FName WeaponMatSlotName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	UMaterial* WeaponMatInvisible;

	FTimerHandle NormalAttackTimer;
	FTimerHandle ShiftTimer;
	FTimerHandle QSkillTimer;
	FTimerHandle ESkillTimer;

	UPROPERTY(BlueprintReadOnly)
	EPrevMoveState PrevMoveState;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetNormalAttackEnd();
	void SetShiftSkillEnd();
	void SetQSkillEnd();
	void SetESkillEnd();

	float GetHealth() const;

	virtual void SetWeaponVisible(bool NewFlag);

	ECharacterAffiliation GetCharacterAffilation() { return CharacterAffiliation; }
	
};
