// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_SetEntrancePos.generated.h"

/**
 * 
 */
UCLASS()
class TESTRPG_API UBTTaskNode_SetEntrancePos : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTaskNode_SetEntrancePos();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

};
