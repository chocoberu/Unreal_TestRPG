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
	int32 AnimIndex = FMath::RandRange(0, NormalAttackArray.Num() - 1);
	if (NormalAttackArray.Num() > 0 && NormalAttackArray[AnimIndex] != nullptr)
		Montage_Play(NormalAttackArray[AnimIndex], 1.0f);
}

void UTEnemyAnimInstance::PlayUppercutAttackMontage()
{
	if (UppercutAttackMontage != nullptr)
		Montage_Play(UppercutAttackMontage, 1.0f);
}

void UTEnemyAnimInstance::PlaySpawnMontage()
{
	if (SpawnMontage != nullptr)
		Montage_Play(SpawnMontage, 1.0f);
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