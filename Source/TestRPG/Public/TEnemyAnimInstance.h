// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TEnemyAnimInstance.generated.h"

using FOnNormalAttackHitCheckDelegate = TMulticastDelegate<void()>;
using FOnEntranceStartDelegate = TMulticastDelegate<void()>;
using FOnEntranceEndDelegate = TMulticastDelegate<void()>;
using FOnUppercutHitCheckDelegate = TMulticastDelegate<void()>;
/**
 * 
 */
UCLASS()
class TESTRPG_API UTEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UTEnemyAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	void SetDeadAnim() { bIsDead = true; }

	void PlayHitMontage();

	void PlaySpawnMontage();

	void PlayNormalAttackMontage();

	void PlayUppercutAttackMontage();

	// µ®∏Æ∞‘¿Ã∆Æ
	FOnNormalAttackHitCheckDelegate OnNormalAttackHitCheckDelegate;
	FOnEntranceStartDelegate OnEntranceStartDelegate;
	FOnEntranceEndDelegate OnEntranceEndDelegate;
	FOnUppercutHitCheckDelegate OnUppercutHitCheckDelegate;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool bIsDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", Meta = (AllowPrivateAccess = true))
	TArray<UAnimMontage*> NormalAttackArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", Meta = (AllowPrivateAccess = true))
	UAnimMontage* HitMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", Meta = (AllowPrivateAccess = true))
	UAnimMontage* SpawnMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", Meta = (AllowPrivateAccess = true))
	UAnimMontage* UppercutAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn", Meta = (AllowPrivateAccess = true))
	float CurrentSpeed;

	UFUNCTION()
	void AnimNotify_NormalAttackCheck();

	UFUNCTION()
	void AnimNotify_EntranceStart();

	UFUNCTION()
	void AnimNotify_EntranceEnd();

	UFUNCTION()
	void AnimNotify_SwingAttackCheck();

	UFUNCTION()
	void AnimNotify_UppercutCheck();
};
