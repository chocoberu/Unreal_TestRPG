// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestItem.h"
#include "TestPotionItem.generated.h"

/**
 * 
 */
UCLASS()
class TESTRPG_API ATestPotionItem : public ATestItem
{
	GENERATED_BODY()
	
public:
	ATestPotionItem();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void UseItem(AActor* OverlapActor) override;


};
