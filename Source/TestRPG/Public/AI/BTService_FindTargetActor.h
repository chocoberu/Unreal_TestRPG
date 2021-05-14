// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TestRPG.h"
#include "BehaviorTree/BTService.h"
#include "BTService_FindTargetActor.generated.h"

class UAISense;
class UAIPerceptionComponent;
/**
 * 
 */
UCLASS()
class TESTRPG_API UBTService_FindTargetActor : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_FindTargetActor();

	UPROPERTY(EditAnywhere, Category = "Class")
	TSubclassOf<UAISense> AISenseSightClass;

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
