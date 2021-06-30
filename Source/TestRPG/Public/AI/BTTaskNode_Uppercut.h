// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_Uppercut.generated.h"

/**
 * 
 */
UCLASS()
class TESTRPG_API UBTTaskNode_Uppercut : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	UBTTaskNode_Uppercut();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	
	bool bUppercut;
};
