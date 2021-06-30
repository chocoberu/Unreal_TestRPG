// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTaskNode_NormalAttack.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "TBaseEnemyCharacter.h"

UBTTaskNode_NormalAttack::UBTTaskNode_NormalAttack()
{
	bNotifyTick = true;
	NodeName = TEXT("AI Normal Attack");
	bAttack = false;
}

void UBTTaskNode_NormalAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if(!bAttack)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}

EBTNodeResult::Type UBTTaskNode_NormalAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto AICharacter = Cast<ATBaseEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (AICharacter == nullptr)
		return EBTNodeResult::Failed;

	AICharacter->NormalAttack();

	AICharacter->OnAttackEnd.AddLambda([this]() -> void {
		bAttack = false;
		});

	bAttack = true;
	return EBTNodeResult::InProgress;
}
