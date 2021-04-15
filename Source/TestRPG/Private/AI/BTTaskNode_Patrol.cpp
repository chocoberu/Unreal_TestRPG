// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/BTTaskNode_Patrol.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTaskNode_Patrol::UBTTaskNode_Patrol()
{
    NodeName = TEXT("Patrol");
}

EBTNodeResult::Type UBTTaskNode_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

    auto AICharacter = OwnerComp.GetAIOwner()->GetPawn();
    if (AICharacter == nullptr)
    {
        UE_LOG(LogTemp, Log, TEXT("Patrol Failed, AICharacter nullptr"));
        return EBTNodeResult::Failed;
    }

    UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
    if (NavSystem == nullptr)
    {
        UE_LOG(LogTemp, Log, TEXT("Patrol Failed, NavSystem nullptr"));
        return EBTNodeResult::Failed;
    }

    FNavLocation NextLocation;
    if (NavSystem->GetRandomPointInNavigableRadius(AICharacter->GetActorLocation(), 500.0f, NextLocation))
    {
        UAIBlueprintHelperLibrary::SimpleMoveToLocation(OwnerComp.GetAIOwner(), NextLocation.Location);
        UE_LOG(LogTemp, Log, TEXT("Patrol (%f, %f, %f)"), NextLocation.Location.X, NextLocation.Location.Y, NextLocation.Location.Z);
        OwnerComp.GetBlackboardComponent()->SetValueAsVector("NextPos", NextLocation.Location);
        
        return EBTNodeResult::Succeeded;
    }
    UE_LOG(LogTemp, Log, TEXT("Patrol Failed"));
    return EBTNodeResult::Failed;
}
