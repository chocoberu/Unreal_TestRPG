// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TPlayerAnimInstance.generated.h"

//DECLARE_MULTICAST_DELEGATE(FOnNormalAttackHitCheckDelegate);
using FOnNormalAttackHitCheckDelegate = TMulticastDelegate<void()>;
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
	
	FOnNormalAttackHitCheckDelegate OnNormalAttackHitCheckDelegate;
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack", Meta = (AllowPrivateAccess = true))
	UAnimMontage* NormalAttackMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack", Meta = (AllowPrivateAccess = true))
	UAnimMontage* ShiftMontage;

private:
	UFUNCTION()
	void AnimNotify_NormalAttackCheck();

};
