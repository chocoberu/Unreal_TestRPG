// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_DistanceToTarget.generated.h"

/**
 * 
 */
UCLASS()
class TESTRPG_API UBTService_DistanceToTarget : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_DistanceToTarget();

protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
