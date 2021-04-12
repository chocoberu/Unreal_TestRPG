// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TPlayerAnimInstance.h"
#include "TwinGunnerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TESTRPG_API UTwinGunnerAnimInstance : public UTPlayerAnimInstance
{
	GENERATED_BODY()
	
public:
	UTwinGunnerAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void PlayNormalAttack();
	virtual void PlayShift();
	virtual void PlayESkill();
	virtual void PlayQSkill();
	virtual void SetChargeEnd();

};
