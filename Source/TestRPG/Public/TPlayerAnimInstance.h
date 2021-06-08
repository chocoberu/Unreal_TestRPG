// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TPlayerAnimInstance.generated.h"

UENUM(BlueprintType)
enum class EPlayerAnimState : uint8
{
	E_Idle = 0 UMETA(DisplayName = "Idle"),
	E_QSkill UMETA(DisplayName = "Q Skill"),
	E_ESkill UMETA(DIsplayName = "E Skill"),
	E_MRButtonSkill UMETA(DisplayName = "Mouse R Skill"),
	E_Dead UMETA(DisplayName = "Dead"),
};

UENUM(BlueprintType)
enum class EChargeSkillState : uint8
{
	E_Idle = 0 UMETA(DisplayName = "Idle"),
	E_Charging UMETA(DisplayName = "Charging"),
	E_Fire UMETA(DisplayName = "Fire"),
};

using FOnNormalAttackHitCheckDelegate = TMulticastDelegate<void()>;
using FOnQSkillCheckDelegate = TMulticastDelegate<void()>;
using FOnQSkillEndDelegate = TMulticastDelegate<void()>;
using FOnESkillStartDelegate = TMulticastDelegate<void()>;
using FOnESkillEndDelegate = TMulticastDelegate<void()>;
/**
 * 
 */
UCLASS()
class TESTRPG_API UTPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UTPlayerAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void PlayNormalAttack();
	virtual void PlayShift(int32 ShiftIndex);
	virtual void PlayESkill();
	virtual void PlayQSkill();

	void SetDeadAnim() { bIsDead = true; }
	virtual void SetChargeEnd();
	
	FOnNormalAttackHitCheckDelegate OnNormalAttackHitCheckDelegate;
	FOnESkillStartDelegate OnESkillStartDelegate;
	FOnESkillEndDelegate OnESkillEndDelegate;
	FOnQSkillCheckDelegate OnQSkillCheckDelegate;
	FOnQSkillEndDelegate OnQSkillEndDelegate;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", Meta = (AllowPrivateAccess = true))
	TArray<UAnimMontage*> NormalAttackArray;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack", Meta = (AllowPrivateAccess = true))
	UAnimMontage* ShiftMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack", Meta = (AllowPrivateAccess = true))
	UAnimMontage* ShiftBackMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack", Meta = (AllowPrivateAccess = true))
	UAnimMontage* ESkillMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack", Meta = (AllowPrivateAccess = true))
	UAnimMontage* QSkillMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool bIsDead;

	int32 CurNormalAttackIndex;

	UPROPERTY(BlueprintReadWrite, Category = "Attack", Meta = (AllowPrivateAccess = true))
	EPlayerAnimState PlayerAnimState;

	UPROPERTY(BlueprintReadOnly, Category = "Attack", Meta = (AllowPrivateAccess = true))
	EChargeSkillState ChargeSkillState;

protected:

	UFUNCTION()
	virtual void AnimNotify_NormalAttackCheck();

	UFUNCTION()
	virtual void AnimNotify_ESkillStart();

	UFUNCTION()
	virtual void AnimNotify_ESkillEnd();

	UFUNCTION()
	virtual void AnimNotify_ResetNormalAttack();

	UFUNCTION()
	virtual void AnimNotify_QSkillCheck();

	UFUNCTION()
	virtual void AnimNotify_QSkillEnd();

	UFUNCTION()
	virtual void AnimNotify_SetCharging();
};
