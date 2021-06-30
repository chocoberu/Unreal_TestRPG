// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTaskNode_SpawnMinion.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "TestSwordBoss.h"

UBTTaskNode_SpawnMinion::UBTTaskNode_SpawnMinion()
{
	NodeName = TEXT("Spawn Minion");
	bNotifyTick = true;
	bSpawn = false;

}

EBTNodeResult::Type UBTTaskNode_SpawnMinion::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ATestSwordBoss* ControllingPawn = Cast<ATestSwordBoss>(OwnerComp.GetAIOwner()->GetPawn());
	if (ControllingPawn == nullptr)
		return EBTNodeResult::Failed;
	
	// 미니언 스폰 불가인 경우 다음 단계로 넘어감
	if (!ControllingPawn->CanSpawn())
		return EBTNodeResult::Succeeded;

	ControllingPawn->SpawnMinion();

	ControllingPawn->OnAttackEnd.AddLambda([this]() {
		bSpawn = false;
		});

	bSpawn = true;
	return EBTNodeResult::InProgress;
}

void UBTTaskNode_SpawnMinion::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!bSpawn)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
