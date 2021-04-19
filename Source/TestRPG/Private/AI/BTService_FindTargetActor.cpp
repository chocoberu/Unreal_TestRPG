// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_FindTargetActor.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "AIController.h"

UBTService_FindTargetActor::UBTService_FindTargetActor()
{
	AISenseSightClass = UAISense_Sight::StaticClass();
}

void UBTService_FindTargetActor::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (ControllingPawn == nullptr)
		return;

	auto AIPerceptionComp = ControllingPawn->FindComponentByClass<UAIPerceptionComponent>();
	if (AIPerceptionComp == nullptr)
		return;

	UE_LOG(LogTemp, Log, TEXT("AIPerception Comp Owner : %s"), *AIPerceptionComp->GetOwner()->GetName());

	TArray<AActor*> ActorArray;
	AIPerceptionComp->GetKnownPerceivedActors(nullptr, ActorArray);
	//AIPerceptionComp->GetPerceivedActors(nullptr, ActorArray);

	UE_LOG(LogTemp, Log, TEXT("Perceived Actors : %d"), ActorArray.Num());
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), nullptr);

	for (auto TargetActor : ActorArray)
	{
		if (TargetActor != nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("Target Actor is : %s"), *TargetActor->GetName());
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), TargetActor);
			break;
		}
	}
}
