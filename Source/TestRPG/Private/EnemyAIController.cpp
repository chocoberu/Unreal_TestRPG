// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"

AEnemyAIController::AEnemyAIController()
{

}
void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	//RunAI();
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyAIController::RunAI()
{
	UseBlackboard(BBAsset, Blackboard);
	RunBehaviorTree(BTAsset);
}

void AEnemyAIController::StopAI()
{
	auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BehaviorTreeComponent != nullptr)
	{
		BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
	}
}