// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_DistanceToTarget.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBTService_DistanceToTarget::UBTService_DistanceToTarget()
{

}

void UBTService_DistanceToTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
		return;

	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (BlackboardComp == nullptr)
		return;

	auto TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject(TEXT("TargetActor")));
	if (TargetActor == nullptr)
		return;

	float DistToTarget = (ControllingPawn->GetActorLocation() - TargetActor->GetActorLocation()).Size();
	BlackboardComp->SetValueAsFloat(TEXT("DistToTarget"), DistToTarget);
}
