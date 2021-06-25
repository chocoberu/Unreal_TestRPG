// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTaskNode_Uppercut.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "TestSwordBoss.h"


UBTTaskNode_Uppercut::UBTTaskNode_Uppercut()
{
	NodeName = TEXT("Uppercut Skill");
	bNotifyTick = false;
}

EBTNodeResult::Type UBTTaskNode_Uppercut::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ATestSwordBoss* ControllingPawn = Cast<ATestSwordBoss>(OwnerComp.GetAIOwner()->GetPawn());
	if (ControllingPawn == nullptr)
		return EBTNodeResult::Failed;

	if (ControllingPawn->CanUppercut())
		ControllingPawn->UppercutAttack();
	else
		ControllingPawn->NormalAttack();

	return EBTNodeResult::Succeeded;
}
