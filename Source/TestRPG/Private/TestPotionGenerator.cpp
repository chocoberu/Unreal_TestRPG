// Fill out your copyright notice in the Description page of Project Settings.


#include "TestPotionGenerator.h"
#include "NavigationSystem.h"
#include "TestPotionItem.h"

// Sets default values
ATestPotionGenerator::ATestPotionGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CurrentPotionCount = 0;
}

// Called when the game starts or when spawned
void ATestPotionGenerator::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ATestPotionGenerator::SpawnPotion, SpawnTime, true);
}

void ATestPotionGenerator::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorldTimerManager().ClearTimer(SpawnTimer);
}

void ATestPotionGenerator::SpawnPotion()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FNavLocation NextLocation;

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (NavSystem == nullptr)
		return;

	FVector ActorLocation = GetActorLocation();
	ActorLocation.Y += 50.0f;

	if (NavSystem->GetRandomPointInNavigableRadius(ActorLocation, RandomRadius, NextLocation))
	{
		ATestPotionItem* Potion = GetWorld()->SpawnActor<ATestPotionItem>(PotionClass, NextLocation.Location, FRotator::ZeroRotator, SpawnParams);
		Potion->SetOwner(this);
	}
}

// Called every frame
void ATestPotionGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

