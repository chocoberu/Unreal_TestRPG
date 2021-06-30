// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordEnemyCharacter.h"
#include "TEnemyAnimInstance.h"
#include "TWeapon.h"
#include "EnemyAIController.h"
#include "DrawDebugHelpers.h"

ASwordEnemyCharacter::ASwordEnemyCharacter()
{
	RightWeaponAttachSocketName = "hand_rWeaponSocket";
	AttackDamage = 10.0f;
}

void ASwordEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	EnemyAnimInstance = Cast<UTEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	EnemyAnimInstance->OnNormalAttackHitCheckDelegate.AddUFunction(this, FName("NormalAttackCheck"));

	// Spawn a default weapon
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	CurrentWeapon = GetWorld()->SpawnActor<ATWeapon>(WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	if (CurrentWeapon)
	{
		CurrentWeapon->SetOwner(this);
		CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, RightWeaponAttachSocketName);
	}

	if (EnemyAIController != nullptr)
	{
		EnemyAIController->RunAI();
	}
}

void ASwordEnemyCharacter::PlayHitMontage()
{
	Super::PlayHitMontage();
	if (bNormalAttack)
	{
		bNormalAttack = false;
		OnAttackEnd.Broadcast();
	}
	EnemyAnimInstance->PlayHitMontage();
}

void ASwordEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASwordEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ASwordEnemyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void ASwordEnemyCharacter::NormalAttack()
{
	Super::NormalAttack();
	UE_LOG(LogTemp, Log, TEXT("SwordEnemyCharacter Normal Attack"));

	EnemyAnimInstance->PlayNormalAttackMontage();
}

void ASwordEnemyCharacter::NormalAttackCheck()
{
	if (bDied)
		return;

	FHitResult HitResult;

	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(), // 시작점
		GetActorLocation() + GetActorForwardVector() * 50.0f, // 끝점
		FQuat::Identity, // 회전값
		ECollisionChannel::ECC_GameTraceChannel2, // 트레이스채널
		FCollisionShape::MakeSphere(50.0f),
		Params);

	// 공격 판정 범위를 DrawDebugCapsule로 표시
#if ENABLE_DRAW_DEBUG
	FVector TraceVec = GetActorForwardVector() * 50.0f;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = 50.0f * 0.5f + 50.0f;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 5.0f;

	DrawDebugCapsule(GetWorld(),
		Center,
		HalfHeight,
		50.0f,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime);
#endif

	if (bResult)
	{
		if (HitResult.Actor.IsValid())
		{
			auto Character = Cast<ACharacter>(HitResult.Actor.Get());
			if (Character == nullptr)
				return;

			UE_LOG(LogTemp, Log, TEXT("SwordEnemy : %s attack"), *Character->GetName());

			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(AttackDamage, // 데미지 크기
				DamageEvent, // 데미지 종류
				GetController(), // 가해자 (컨트롤러)
				this); // 데미지 전달을 위해 사용한 도구 (액터)
		}
	}
}