// Fill out your copyright notice in the Description page of Project Settings.


#include "TestSlash.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PlayerCharacter.h"
#include "THealthComponent.h"

// Sets default values
ATestSlash::ATestSlash()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ParticleSystemComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));

	RootComponent = SphereComp;
	StaticMeshComp->SetupAttachment(RootComponent);
	ParticleSystemComp->SetupAttachment(RootComponent);
	MovementComp->SetUpdatedComponent(SphereComp);
	MovementComp->bRotationFollowsVelocity = true;
	
	StaticMeshComp->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

}

// Called when the game starts or when spawned
void ATestSlash::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(SlashLifeTime);
}

// Called every frame
void ATestSlash::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATestSlash::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	auto Player = Cast<ACharacter>(OtherActor);
	if (Player != nullptr)
	{
		FDamageEvent DamageEvent;
		Player->TakeDamage(AttackDamage, DamageEvent, nullptr, GetOwner());
		UE_LOG(LogTemp, Log, TEXT("Slash Overlap %s"), *OtherActor->GetName());
	}
	SetActorHiddenInGame(true);
}

void ATestSlash::SetSlashDirection(const FVector SlashDirection)
{
	MovementComp->Velocity = SlashDirection * MovementComp->InitialSpeed;
}

