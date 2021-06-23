// Fill out your copyright notice in the Description page of Project Settings.


#include "THealthComponent.h"
#include "TPlayerAnimInstance.h"

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

	AActor* Owner = GetOwner();

	if (Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UTHealthComponent::HandleTakeAnyDamage);
	}
	
	Health = DefaultHealth;
}

void UTHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || bIsDead)
		return;
	// TODO : 같은 팀에게 받은 데미지 무시

	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);
	UE_LOG(LogTemp, Log, TEXT("Health Changed : %s"), *FString::SanitizeFloat(Health));

	bIsDead = Health <= 0.0f;
	
	OnHealthChanged.Broadcast(this, Health, Damage, DamageType, InstigatedBy, DamageCauser);

	if (bIsDead)
	{
		// TODO : 처리
	}
}


// Called every frame
void UTHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

float UTHealthComponent::GetHealth() const
{
	return Health;
}

float UTHealthComponent::GetDefaultHealth() const
{
	return DefaultHealth;
}

float UTHealthComponent::GetHPRatio() const
{
	return Health < KINDA_SMALL_NUMBER ? 0.0f : (Health / DefaultHealth);
}

void UTHealthComponent::SetHealth(float NewHealth)
{
	Health = FMath::Clamp(NewHealth, 0.0f, DefaultHealth);
	OnHealthChanged.Broadcast(this, Health, 0.0f, nullptr, nullptr, nullptr);
}