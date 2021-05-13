// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTaskNode_SpawnMinion.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "TestSwordBoss.h"

UBTTaskNode_SpawnMinion::UBTTaskNode_SpawnMinion()
{
	NodeName = TEXT("AI Normal Attack");
	bNotifyTick = false;
}
EBTNodeResult::Type UBTTaskNode_SpawnMinion::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UE_LOG(LogTemp, Log, TEXT("TODO : Boss Spawn Minion"));

	ATestSwordBoss* ControllingPawn = Cast<ATestSwordBoss>(OwnerComp.GetAIOwner()->GetPawn());
	if (ControllingPawn == nullptr)
		return EBTNodeResult::Failed;
	
	ControllingPawn->SpawnMinion();

	return EBTNodeResult::Succeeded;
}
