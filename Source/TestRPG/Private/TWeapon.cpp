// Fill out your copyright notice in the Description page of Project Settings.


#include "TWeapon.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ATWeapon::ATWeapon()
{
 	
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComop"));
	MeshComp->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
}

// Called when the game starts or when spawned
void ATWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}


