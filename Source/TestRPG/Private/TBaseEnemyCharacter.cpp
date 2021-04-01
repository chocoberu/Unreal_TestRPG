// Fill out your copyright notice in the Description page of Project Settings.


#include "TBaseEnemyCharacter.h"
#include "THealthComponent.h"

// Sets default values
ATBaseEnemyCharacter::ATBaseEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UTHealthComponent>(TEXT("HealthComp"));

}

// Called when the game starts or when spawned
void ATBaseEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATBaseEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATBaseEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

