// Fill out your copyright notice in the Description page of Project Settings.


#include "TwinGunnerUltimateGun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
ATwinGunnerUltimateGun::ATwinGunnerUltimateGun()
{
	CapsuleComp = CreateDefaultSubobject< UCapsuleComponent>(TEXT("CapsuleComp"));
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = CapsuleComp;
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	// Particle Component
	LeftShellEjectionComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("LeftShellEjection"));
	RightShellEjectionComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("RightShellEjection"));
	LeftMuzzleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("LeftMuzzle"));
	RightMuzzleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("RightMuzzle"));
	LeftShoulderComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("LeftShoulder"));
	RightShoulderComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("RightShoulder"));

	LeftShellEjectSocket = TEXT("FX_Ult_ShellEject_L");
	RightShellEjectSocket = TEXT("FX_Ult_ShellEject_R");
	LeftMuzzleSocket = TEXT("Muzzle_04");
	RightMuzzleSocket = TEXT("Muzzle_03");
	LeftShoulderSocket = TEXT("FX_Ult_Shoulder_l");
	RightShoulderSocket = TEXT("FX_Ult_Shoulder_r");

	LeftShellEjectionComp->SetupAttachment(MeshComp, LeftShellEjectSocket);
	RightShellEjectionComp->SetupAttachment(MeshComp, RightShellEjectSocket);
	LeftMuzzleComp->SetupAttachment(MeshComp, LeftMuzzleSocket);
	RightMuzzleComp->SetupAttachment(MeshComp, RightMuzzleSocket);
	LeftShoulderComp->SetupAttachment(MeshComp, LeftShoulderSocket);
	RightShoulderComp->SetupAttachment(MeshComp, RightShoulderSocket);
}

// Called when the game starts or when spawned
void ATwinGunnerUltimateGun::BeginPlay()
{
	Super::BeginPlay();
	SetActorHiddenInGame(true);
}

// Called every frame
void ATwinGunnerUltimateGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATwinGunnerUltimateGun::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ATwinGunnerUltimateGun::SetWeaponVisible(bool NewFlag)
{

}


void ATwinGunnerUltimateGun::StartUltimaeAttack()
{
	SetActorHiddenInGame(false);
	GetWorldTimerManager().SetTimer(UltimateAttackCheckTimer, this, &ATwinGunnerUltimateGun::UltimateAttackCheck, UltimateAttackCheckTime, true);
	
}

void ATwinGunnerUltimateGun::EndUltimateAttack()
{
	SetActorHiddenInGame(true);
	GetWorldTimerManager().ClearTimer(UltimateAttackCheckTimer);

	LeftMuzzleComp->Deactivate();
	RightMuzzleComp->Deactivate();
	LeftShellEjectionComp->Deactivate();
	RightShellEjectionComp->Deactivate();
	LeftShoulderComp->Deactivate();
	RightShoulderComp->Deactivate();
}

void ATwinGunnerUltimateGun::UltimateAttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);

	auto UltGunOwner = Cast<APawn>(GetOwner());
	auto Controller = UltGunOwner->GetController();
	if (UltGunOwner == nullptr || Controller == nullptr)
	{
		GetWorldTimerManager().ClearTimer(UltimateAttackCheckTimer);
		return;
	}
	Params.AddIgnoredActor(UltGunOwner);
	
	FRotator AttackRot = Controller->GetControlRotation();
	FVector AttackStart;
	UltGunOwner->GetActorEyesViewPoint(AttackStart, AttackRot);
	//GetActorEyesViewPoint(AttackStart, AttackRot);
	FVector AttackEnd = AttackStart + AttackRot.Vector() * AttackRange;

	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		AttackStart, // 시작점
		AttackEnd, // 끝점
		FQuat::Identity, // 회전값
		ECollisionChannel::ECC_GameTraceChannel2, // 트레이스채널
		FCollisionShape::MakeSphere(AttackRadius),
		Params);
	
	FColor DebugColor = bResult ? FColor::Green : FColor::Red;
	DrawDebugLine(GetWorld(), AttackStart, AttackEnd, DebugColor, false, 1.0f);

	if (bResult)
	{
		if (HitResult.Actor.IsValid())
		{
			auto Character = Cast<ACharacter>(HitResult.Actor.Get());
			if (Character == nullptr)
				return;

			UE_LOG(LogTemp, Log, TEXT("%s attack"), *Character->GetName());

			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(AttackDamage, // 데미지 크기
				DamageEvent, // 데미지 종류
				Controller, // 가해자 (컨트롤러)
				this); // 데미지 전달을 위해 사용한 도구 (액터)

			// 타격 파티클 생성
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), AttackHitParticle, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());
		}
	}
	else
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), AttackNoHitParticle, AttackEnd, FRotator::ZeroRotator);
	}
	LeftMuzzleComp->Activate(false);
	RightMuzzleComp->Activate(false);
	LeftShellEjectionComp->Activate(false);
	RightShellEjectionComp->Activate(false);
	LeftShoulderComp->Activate(true);
	RightShoulderComp->Activate(true);
}