// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_SpawnMinion.generated.h"

/**
 * 
 */
UCLASS()
class TESTRPG_API UBTTaskNode_SpawnMinion : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTaskNode_SpawnMinion();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
