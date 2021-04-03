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
