// Fill out your copyright notice in the Description page of Project Settings.


#include "TEnemyAnimInstance.h"

UTEnemyAnimInstance::UTEnemyAnimInstance()
{
	bIsDead = false;
}

void UTEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	CurrentSpeed = GetOwningActor()->GetVelocity().Size();
}

void UTEnemyAnimInstance::PlayHitMontage()
{
	if (HitMontage != nullptr)
		Montage_Play(HitMontage, 1.2f);
}

void UTEnemyAnimInstance::PlayNormalAttackMontage()
{
	if (NormalAttackArray.Num() > 0 && NormalAttackArray[0] != nullptr)
		Montage_Play(NormalAttackArray[0], 1.0f);
}

void UTEnemyAnimInstance::AnimNotify_NormalAttackCheck()
{
	OnNormalAttackHitCheckDelegate.Broadcast();
}

void UTEnemyAnimInstance::AnimNotify_EntranceStart()
{
	OnEntranceStartDelegate.Broadcast();
}

void UTEnemyAnimInstance::AnimNotify_EntranceEnd()
{
	OnEntranceEndDelegate.Broadcast();
}

void UTEnemyAnimInstance::AnimNotify_SwingAttackCheck()
{
	OnNormalAttackHitCheckDelegate.Broadcast();
}