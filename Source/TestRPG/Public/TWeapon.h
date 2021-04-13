// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TWeapon.generated.h"

UCLASS()
class TESTRPG_API ATWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Components

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USkeletalMeshComponent* MeshComp;

public:	
	

};
