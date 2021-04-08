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

using FOnNormalAttackHitCheckDelegate = TMulticastDelegate<void()>;
using FOnQSkillCheckDelegate = TMulticastDelegate<void()>;
using FOnQSkillEndDelegate = TMulticastDelegate<void()>;
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

	void PlayNormalAttack();
	void PlayShift();
	void PlayESkill();
	void PlayQSkill();

	void SetDeadAnim() { bIsDead = true; }
	
	FOnNormalAttackHitCheckDelegate OnNormalAttackHitCheckDelegate;
	FOnESkillEndDelegate OnESkillEndDelegate;
	FOnQSkillCheckDelegate OnQSkillCheckDelegate;
	FOnQSkillEndDelegate OnQSkillEndDelegate;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", Meta = (AllowPrivateAccess = true))
	TArray<UAnimMontage*> NormalAttackArray;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack", Meta = (AllowPrivateAccess = true))
	UAnimMontage* ShiftMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack", Meta = (AllowPrivateAccess = true))
	UAnimMontage* ESkillMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack", Meta = (AllowPrivateAccess = true))
	UAnimMontage* QSkillMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool bIsDead;

	int32 CurNormalAttackIndex;

	UPROPERTY(BlueprintReadWrite, Category = "Attack", Meta = (AllowPrivateAccess = true))
	EPlayerAnimState PlayerAnimState;

private:
	UFUNCTION()
	void AnimNotify_NormalAttackCheck();

	UFUNCTION()
	void AnimNotify_ESkillEnd();

	UFUNCTION()
	void AnimNotify_ResetNormalAttack();

	UFUNCTION()
	void AnimNotify_QSkillCheck();

	UFUNCTION()
	void AnimNotify_QSkillEnd();

};
