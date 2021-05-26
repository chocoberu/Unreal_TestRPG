// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestPotionGenerator.generated.h"

class ATestPotionItem;

UCLASS()
class TESTRPG_API ATestPotionGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestPotionGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void SpawnPotion();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Potion")
	TSubclassOf<ATestPotionItem> PotionClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Potion")
	float SpawnTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Potion")
	float RandomRadius;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Potion")
	int32 MaxCount;

	int32 CurrentPotionCount;

	FTimerHandle SpawnTimer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
