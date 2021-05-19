// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestItem.generated.h"

UCLASS()
class TESTRPG_API ATestItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestItem();

protected:

	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCapsuleComponent* CapsuleComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	virtual void UseItem(AActor* OverlapActor);

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
};
