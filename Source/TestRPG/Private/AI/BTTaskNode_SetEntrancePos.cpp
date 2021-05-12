// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTaskNode_SetEntrancePos.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"


UBTTaskNode_SetEntrancePos::UBTTaskNode_SetEntrancePos()
{
    NodeName = TEXT("Set Entrance Position");
    bNotifyTick = false;
}

EBTNodeResult::Type UBTTaskNode_SetEntrancePos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (ControllingPawn == nullptr)
        return EBTNodeResult::Failed;

    OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("NextPos"), ControllingPawn->GetActorLocation() + ControllingPawn->GetActorForwardVector() * 400.0f);

    return EBTNodeResult::Succeeded;
}

