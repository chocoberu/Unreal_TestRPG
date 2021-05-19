// Fill out your copyright notice in the Description page of Project Settings.

#include "TestPotionItem.h"

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

	// TODO : HP 회복 구현
}
