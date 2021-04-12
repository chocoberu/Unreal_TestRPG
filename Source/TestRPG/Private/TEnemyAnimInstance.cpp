// Fill out your copyright notice in the Description page of Project Settings.


#include "TEnemyAnimInstance.h"

UTEnemyAnimInstance::UTEnemyAnimInstance()
{
	bIsDead = false;
}

void UTEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

}

void UTEnemyAnimInstance::PlayHitMontage()
{
	if (HitMontage != nullptr)
		Montage_Play(HitMontage, 1.2f);
}
