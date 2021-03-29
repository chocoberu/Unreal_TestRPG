// Fill out your copyright notice in the Description page of Project Settings.


#include "THealthComponent.h"

// Sets default values for this component's properties
UTHealthComponent::UTHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	DefaultHealth = 100.0f;
}


// Called when the game starts
void UTHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	Health = DefaultHealth;
}


// Called every frame
void UTHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UTHealthComponent::GetHealth() const
{
	return Health;
}

