// Fill out your copyright notice in the Description page of Project Settings.


#include "TestSlash.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PlayerCharacter.h"
#include "THealthComponent.h"

// Sets default values
ATestSlash::ATestSlash()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	ParticleSystemComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));

	RootComponent = SphereComp;
	ParticleSystemComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATestSlash::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestSlash::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//SphereComp->AddForce(GetActorForwardVector());
}

void ATestSlash::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	auto Player = Cast<APlayerCharacter>(OtherActor);
	if (Player != nullptr)
	{
		FDamageEvent DamageEvent;
		Player->TakeDamage(AttackDamage, DamageEvent, nullptr, GetOwner());
	}
}

