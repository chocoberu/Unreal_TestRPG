// Fill out your copyright notice in the Description page of Project Settings.


#include "TwinGunnerUltimateGun.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ATwinGunnerUltimateGun::ATwinGunnerUltimateGun()
{
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComop"));
	MeshComp->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	RootComponent = MeshComp;
}

// Called when the game starts or when spawned
void ATwinGunnerUltimateGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATwinGunnerUltimateGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATwinGunnerUltimateGun::SetWeaponVisible(bool NewFlag)
{

}
