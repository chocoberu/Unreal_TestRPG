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
	EnemyAnimInstance->OnNormalAttackHitCheckDelegate.AddUObject(this, &ASwordEnemyCharacter::NormalAttackCheck);

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

void ASwordEnemyCharacter::NormalAttack()
{
	Super::NormalAttack();
	UE_LOG(LogTemp, Log, TEXT("SwordEnemyCharacter Normal Attack"));

	EnemyAnimInstance->PlayNormalAttackMontage();
}

void ASwordEnemyCharacter::NormalAttackCheck()
{
	FHitResult HitResult;

	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(), // ������
		GetActorLocation() + GetActorForwardVector() * 50.0f, // ����
		FQuat::Identity, // ȸ����
		ECollisionChannel::ECC_GameTraceChannel2, // Ʈ���̽�ä��
		FCollisionShape::MakeSphere(50.0f),
		Params);

	// ���� ���� ������ DrawDebugCapsule�� ǥ��
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
			HitResult.Actor->TakeDamage(AttackDamage, // ������ ũ��
				DamageEvent, // ������ ����
				GetController(), // ������ (��Ʈ�ѷ�)
				this); // ������ ������ ���� ����� ���� (����)
		}
	}
}