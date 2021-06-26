// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestSlash.generated.h"

UCLASS()
class TESTRPG_API ATestSlash : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestSlash();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UParticleSystemComponent* ParticleSystemComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	float DefaultMaxSpeed;

	UPROPERTY(EditAnywhere, Category = "Attack")
	float AttackDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	float SlashLifeTime;

	FTimerHandle SlashLifeTimer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
