// Fill out your copyright notice in the Description page of Project Settings.


#include "TPlayerAnimInstance.h"

UTPlayerAnimInstance::UTPlayerAnimInstance()
{
	bIsDead = false;
	CurNormalAttackIndex = 0;
	PlayerAnimState = EPlayerAnimState::E_Idle;
	ChargeSkillState = EChargeSkillState::E_Idle;
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
	
	PlayerAnimState = EPlayerAnimState::E_ESkill;
	CurNormalAttackIndex = 0;
}

void UTPlayerAnimInstance::PlayQSkill()
{
	/*if (PlayerAnimState == EPlayerAnimState::E_QSkill)
		return;*/

	if (QSkillMontage != nullptr)
		Montage_Play(QSkillMontage, 1.0f);
	PlayerAnimState = EPlayerAnimState::E_QSkill;
	CurNormalAttackIndex = 0;
}

void UTPlayerAnimInstance::AnimNotify_NormalAttackCheck()
{
	OnNormalAttackHitCheckDelegate.Broadcast();
}

void UTPlayerAnimInstance::AnimNotify_ESkillStart()
{
	OnESkillStartDelegate.Broadcast();
}

void UTPlayerAnimInstance::AnimNotify_ESkillEnd()
{
	OnESkillEndDelegate.Broadcast();
	PlayerAnimState = EPlayerAnimState::E_Idle;
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
	PlayerAnimState = EPlayerAnimState::E_Idle;
	ChargeSkillState = EChargeSkillState::E_Idle;
	OnQSkillEndDelegate.Broadcast();
}

void UTPlayerAnimInstance::SetChargeEnd()
{
	if (ChargeSkillState == EChargeSkillState::E_Fire)
		return;

	else if (ChargeSkillState == EChargeSkillState::E_Charging)
		ChargeSkillState = EChargeSkillState::E_Fire;
	else
		ChargeSkillState = EChargeSkillState::E_Charging;
}

void UTPlayerAnimInstance::AnimNotify_SetCharging()
{
	if (ChargeSkillState == EChargeSkillState::E_Charging)
		ChargeSkillState = EChargeSkillState::E_Fire;
	else
		ChargeSkillState = EChargeSkillState::E_Charging;
}