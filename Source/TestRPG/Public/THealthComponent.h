// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "THealthComponent.generated.h"

using FOnHealthChangedDelegate = TMulticastDelegate<void(class UTHealthComponent* OwningHealthComp, float Health, float HealthDelta, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)>;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTRPG_API UTHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
			AController* InstigatedBy, AActor* DamageCauser);

	UPROPERTY(EditDefaultsOnly, Category = "HealthComponent")
	float Health;

	UPROPERTY(EditDefaultsOnly, Category = "HealthComponent")
	float DefaultHealth;

	bool bIsDead;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float GetHealth() const;
	float GetHPRatio() const;

	FOnHealthChangedDelegate OnHealthChanged;
};
