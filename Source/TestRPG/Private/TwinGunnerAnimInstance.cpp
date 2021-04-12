// Fill out your copyright notice in the Description page of Project Settings.


#include "TwinGunnerAnimInstance.h"

UTwinGunnerAnimInstance::UTwinGunnerAnimInstance()
{

}

void UTwinGunnerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UTwinGunnerAnimInstance::PlayNormalAttack()
{
	Super::PlayNormalAttack();

}

void UTwinGunnerAnimInstance::PlayShift()
{
	Super::PlayShift();

}

void UTwinGunnerAnimInstance::PlayESkill()
{
	Super::PlayESkill();
}

void UTwinGunnerAnimInstance::PlayQSkill()
{
	if (PlayerAnimState == EPlayerAnimState::E_QSkill)
		return;
	Super::PlayQSkill();

}

void UTwinGunnerAnimInstance::SetChargeEnd()
{
	Super::SetChargeEnd();

}
