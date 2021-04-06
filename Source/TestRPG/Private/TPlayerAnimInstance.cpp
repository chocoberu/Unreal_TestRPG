// Fill out your copyright notice in the Description page of Project Settings.


#include "TPlayerAnimInstance.h"

UTPlayerAnimInstance::UTPlayerAnimInstance()
{
	bIsDead = false;
	CurNormalAttackIndex = 0;
	PlayerAnimState = EPlayerAnimState::E_Idle;
}

void UTPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UTPlayerAnimInstance::PlayNormalAttack()
{
	UE_LOG(LogTemp, Log, TEXT("Normal Attack"));

	if (NormalAttackArray.Num() <= 0)
		return;
	if (NormalAttackArray[CurNormalAttackIndex] != nullptr)
	{
		Montage_Play(NormalAttackArray[CurNormalAttackIndex], 1.0f);
		CurNormalAttackIndex = (CurNormalAttackIndex + 1) % NormalAttackArray.Num();
	}
}

void UTPlayerAnimInstance::PlayShift()
{
	UE_LOG(LogTemp, Log, TEXT("Shift"));

	if (ShiftMontage != nullptr)
		Montage_Play(ShiftMontage, 1.0f);
}

void UTPlayerAnimInstance::PlayESkill()
{
	if (ESkillMontage != nullptr)
		Montage_Play(ESkillMontage, 1.0f);

	CurNormalAttackIndex = 0;
}

void UTPlayerAnimInstance::PlayQSkill()
{
	if (QSkillMontage != nullptr)
		Montage_Play(QSkillMontage, 1.0f);

	CurNormalAttackIndex = 0;
}

void UTPlayerAnimInstance::AnimNotify_NormalAttackCheck()
{
	OnNormalAttackHitCheckDelegate.Broadcast();
}

void UTPlayerAnimInstance::AnimNotify_ESkillEnd()
{
	OnESkillEndDelegate.Broadcast();
}

void UTPlayerAnimInstance::AnimNotify_ResetNormalAttack()
{
	CurNormalAttackIndex = 0;
}

void UTPlayerAnimInstance::AnimNotify_QSkillCheck()
{
	OnQSkillCheckDelegate.Broadcast();
}

void UTPlayerAnimInstance::AnimNotify_QSkillEnd()
{
	OnQSkillEndDelegate.Broadcast();
}