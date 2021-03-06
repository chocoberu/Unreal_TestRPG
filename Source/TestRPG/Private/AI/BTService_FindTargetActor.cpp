// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_FindTargetActor.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "AIController.h"
#include "THealthComponent.h"
#include "PlayerCharacter.h"

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

	//UE_LOG(LogTemp, Log, TEXT("Perceived Actors : %d"), ActorArray.Num());
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), nullptr);
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("NextPos"), ControllingPawn->GetActorLocation());

	if (ActorArray.Num() == 0)
		return;

	float Length = 100000.0f;

	AActor* FinalTarget = nullptr;

	for (auto TargetActor : ActorArray)
	{
		if (TargetActor != nullptr)
		{
			auto PlayerCharacter = Cast<APlayerCharacter>(TargetActor);
			if (PlayerCharacter == nullptr || PlayerCharacter->GetHealth() <= 0.0f ||
				PlayerCharacter->GetCharacterAffilation() != ECharacterAffiliation::E_Player)
				continue;
			
			if (Length > (ControllingPawn->GetActorLocation() - TargetActor->GetActorLocation()).Size())
			{
				Length = (ControllingPawn->GetActorLocation() - TargetActor->GetActorLocation()).Size();
				FinalTarget = TargetActor;
			}
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), FinalTarget);
	OwnerComp.GetBlackboardComponent()->SetValueAsEnum(TEXT("BossState"), (uint8)EEnemyState::E_Patrol);

	if (FinalTarget != nullptr)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("NextPos"), FinalTarget->GetActorLocation());
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(TEXT("BossState"), (uint8)EEnemyState::E_Chasing);
	}
	
}
