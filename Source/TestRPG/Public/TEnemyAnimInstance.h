// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TEnemyAnimInstance.generated.h"

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

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool bIsDead;
};
