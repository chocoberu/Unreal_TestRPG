// Fill out your copyright notice in the Description page of Project Settings.

#include "TestPotionItem.h"
#include "PlayerCharacter.h"
#include "THealthComponent.h"

ATestPotionItem::ATestPotionItem()
{

}

void ATestPotionItem::BeginPlay()
{
	Super::BeginPlay();
}

void ATestPotionItem::UseItem(AActor* OverlapActor)
{
	if (OverlapActor == nullptr)
		return;

	UE_LOG(LogTemp, Log, TEXT("Potion : HP heal"));

	auto Player = Cast<APlayerCharacter>(OverlapActor);
	if (Player == nullptr)
		return;

	auto HealthComp = Cast<UTHealthComponent>(Player->GetComponentByClass(HealthComponentClass));
	if (HealthComp == nullptr)
		return;

	HealthComp->SetHealth(HealthComp->GetHealth() + HealAmount);
}
