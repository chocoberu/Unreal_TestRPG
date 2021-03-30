// Fill out your copyright notice in the Description page of Project Settings.


#include "TPlayerAnimInstance.h"

UTPlayerAnimInstance::UTPlayerAnimInstance()
{
	bIsDead = false;
}

void UTPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);


}

void UTPlayerAnimInstance::PlayNormalAttack()
{
	UE_LOG(LogTemp, Log, TEXT("Normal Attack"));

	if (NormalAttackMontage != nullptr)
		Montage_Play(NormalAttackMontage, 1.0f);
}

void UTPlayerAnimInstance::PlayShift()
{
	UE_LOG(LogTemp, Log, TEXT("Shift"));

	if (ShiftMontage != nullptr)
		Montage_Play(ShiftMontage, 1.0f);
}
void UTPlayerAnimInstance::AnimNotify_NormalAttackCheck()
{
	OnNormalAttackHitCheckDelegate.Broadcast();
}
