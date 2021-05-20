// Fill out your copyright notice in the Description page of Project Settings.


#include "TestItem.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "PlayerCharacter.h"

// Sets default values
ATestItem::ATestItem()
{
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComop"));
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComop"));

	RootComponent = CapsuleComp;
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
}

// Called when the game starts or when spawned
void ATestItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATestItem::UseItem(AActor* OverlapActor)
{

}

void ATestItem::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor == nullptr)
		return;
	UE_LOG(LogTemp, Log, TEXT("Item : Overlap %s"), *OtherActor->GetName());

	auto Player = Cast<APlayerCharacter>(OtherActor);
	
	if(Player != nullptr)
		UseItem(OtherActor);
}


