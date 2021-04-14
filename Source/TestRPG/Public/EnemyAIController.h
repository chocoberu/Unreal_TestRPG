// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class TESTRPG_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemyAIController();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;

	void RunAI();
	void StopAI();
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UBehaviorTree* BTAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UBlackboardData* BBAsset;
};
