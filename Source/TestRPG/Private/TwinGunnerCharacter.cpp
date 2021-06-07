// Fill out your copyright notice in the Description page of Project Settings.


#include "TwinGunnerCharacter.h"
#include "TPlayerAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "TwinGunnerUltimateGun.h"
#include "Particles/ParticleSystemComponent.h"

ATwinGunnerCharacter::ATwinGunnerCharacter()
{
	AttackRange = 500.0f;
	AttackRadius = 50.0f;

	MuzzleSocket = TEXT("Muzzle_01");
	TwinGunnerSkillState = ETwinGunnerSkillState::E_Idle;
	UltimateGunSokcet = FName(TEXT("FX_Ult_Reticule_Main"));

	bQSkillReleased = true;

	NormalAttackDamage = 10.0f;
	QSkillAttackDamage = 30.0f;
}

void ATwinGunnerCharacter::BeginPlay()
{
	Super::BeginPlay();

	AnimInstance = Cast<UTPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	if(AnimInstance == nullptr)
		UE_LOG(LogTemp, Error, TEXT("AnimInstance is nullptr"));

	AnimInstance->OnNormalAttackHitCheckDelegate.AddUObject(this, &ATwinGunnerCharacter::NormalAttackCheck);
	AnimInstance->OnESkillEndDelegate.AddUObject(this, &ATwinGunnerCharacter::SetESkillEnd);
	AnimInstance->OnQSkillCheckDelegate.AddUObject(this, &ATwinGunnerCharacter::QSkillCheck);
	AnimInstance->OnQSkillEndDelegate.AddUObject(this, &ATwinGunnerCharacter::SetQSkillEnd);
	AnimInstance->OnESkillStartDelegate.AddUObject(this, &ATwinGunnerCharacter::SpawnUltimateGun);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	UltimateGun = GetWorld()->SpawnActor<ATwinGunnerUltimateGun>(UltimateGunClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	
	if (UltimateGun)
	{
		UltimateGun->SetOwner(this);
		UltimateGun->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, UltimateGunSokcet);
		UltimateGun->SetActorHiddenInGame(true);
	}
}

// Called every frame
void ATwinGunnerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATwinGunnerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("NormalAttack", EInputEvent::IE_Pressed, this, &ATwinGunnerCharacter::NormalAttack);
	PlayerInputComponent->BindAction("Shift", EInputEvent::IE_Pressed, this, &ATwinGunnerCharacter::Shift);
	PlayerInputComponent->BindAction("E", EInputEvent::IE_Pressed, this, &ATwinGunnerCharacter::ESkill);
	PlayerInputComponent->BindAction("Q", EInputEvent::IE_Pressed, this, &ATwinGunnerCharacter::QSkill);
	PlayerInputComponent->BindAction("Q", EInputEvent::IE_Released, this, &ATwinGunnerCharacter::QSkillReleased);
}

void ATwinGunnerCharacter::NormalAttack()
{
	if (bNormalAttack || TwinGunnerSkillState != ETwinGunnerSkillState::E_Idle || bDied)
		return;
	if (AnimInstance != nullptr)
	{
		AnimInstance->PlayNormalAttack();
		bNormalAttack = true;
		GetWorldTimerManager().SetTimer(NormalAttackTimer, this, &APlayerCharacter::SetNormalAttackEnd, NormalAttackCoolTime, false);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("AnimInstance is nullptr"));
	
}

void ATwinGunnerCharacter::Shift()
{
	if (bShift || TwinGunnerSkillState != ETwinGunnerSkillState::E_Idle || bDied)
		return;

	// 테스트 코드
	// TOOD : 이동 방향 별로 Shift 처리
	switch (PrevMoveState)
	{
	case EPrevMoveState::E_W:
		UE_LOG(LogTemp, Log, TEXT("W Shift"));
		break;
	case EPrevMoveState::E_S:
		UE_LOG(LogTemp, Log, TEXT("S Shift"));
		break;
	case EPrevMoveState::E_A:
		UE_LOG(LogTemp, Log, TEXT("A Shift"));
		break;
	case EPrevMoveState::E_D:
		UE_LOG(LogTemp, Log, TEXT("D Shift"));
		break;
	case EPrevMoveState::E_None:
		UE_LOG(LogTemp, Log, TEXT("None Shift"));
		break;
	}
	
	if (AnimInstance != nullptr)
	{
		AnimInstance->PlayShift();
		// 테스트 코드
		float Velocity = 900.0f; // 순간 속도
		GetCharacterMovement()->Velocity = GetActorForwardVector() * Velocity;
		Jump();

		bShift = true;
		GetWorldTimerManager().SetTimer(ShiftTimer, this, &APlayerCharacter::SetShiftSkillEnd, ShiftSkillCoolTime, false);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("AnimInstance is nullptr"));

}

void ATwinGunnerCharacter::SpawnUltimateGun()
{
	if (AnimInstance != nullptr)
		UltimateGun->StartUltimaeAttack();
}

void ATwinGunnerCharacter::ESkill()
{
	if (bESkill || TwinGunnerSkillState != ETwinGunnerSkillState::E_Idle || bDied)
		return;
	if (AnimInstance != nullptr)
	{
		AnimInstance->PlayESkill();
		TwinGunnerSkillState = ETwinGunnerSkillState::E_UltimateGun;

		bESkill = true;
	}
}

void ATwinGunnerCharacter::SetESkillEnd()
{
	UltimateGun->EndUltimateAttack();
	TwinGunnerSkillState = ETwinGunnerSkillState::E_Idle;
	GetWorldTimerManager().SetTimer(ESkillTimer, this, &APlayerCharacter::SetESkillEnd, ESkillCoolTime, false);
}

void ATwinGunnerCharacter::QSkill()
{
	if (bQSkill || TwinGunnerSkillState != ETwinGunnerSkillState::E_Idle || bDied)
		return;

	if (AnimInstance != nullptr)
	{
		AnimInstance->PlayQSkill();
		TwinGunnerSkillState = ETwinGunnerSkillState::E_ChargeBlast;
		bQSkill = true;
		
	}
}

void ATwinGunnerCharacter::QSkillReleased()
{
	if (TwinGunnerSkillState != ETwinGunnerSkillState::E_ChargeBlast || !bQSkillReleased)
		return;
	if (AnimInstance != nullptr)
	{
		AnimInstance->SetChargeEnd();
		bQSkillReleased = false;
		
	}
}

void ATwinGunnerCharacter::SetQSkillEnd()
{
	TwinGunnerSkillState = ETwinGunnerSkillState::E_Idle;
	bQSkillReleased = true;
	GetWorldTimerManager().SetTimer(QSkillTimer, this, &APlayerCharacter::SetQSkillEnd, QSkillCoolTime, false);
}

void ATwinGunnerCharacter::SetWeaponVisible(bool NewFlag)
{
	if(!NewFlag)
		GetMesh()->SetMaterialByName(WeaponMatSlotName, WeaponMatInvisible);
}

bool ATwinGunnerCharacter::SweepAttackCheck(FHitResult& HitResult, FVector& AttackEnd, float SkillRange, float SkillRadius)
{
	FCollisionQueryParams Params(NAME_None, false, this);

	FRotator AttackRot;
	FVector AttackStart;
	GetActorEyesViewPoint(AttackStart, AttackRot);
	AttackEnd = AttackStart + AttackRot.Vector() * SkillRange;

	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		AttackStart, // 시작점
		AttackEnd, // 끝점
		FQuat::Identity, // 회전값
		ECollisionChannel::ECC_GameTraceChannel2, // 트레이스채널
		FCollisionShape::MakeSphere(SkillRadius),
		Params);

	// Debug 관련
	FColor DebugColor = bResult ? FColor::Green : FColor::Red;
	DrawDebugLine(GetWorld(), AttackStart, AttackEnd, DebugColor, false, 1.0f);

	return bResult;
}

void ATwinGunnerCharacter::NormalAttackCheck()
{
	if (bDied)
		return;

	FHitResult HitResult;
	FVector AttackEnd;

	bool bResult = SweepAttackCheck(HitResult, AttackEnd, AttackRange, AttackRadius);

	if (bResult)
	{
		if (HitResult.Actor.IsValid())
		{
			auto Character = Cast<ACharacter>(HitResult.Actor.Get());
			if (Character == nullptr)
				return;

			UE_LOG(LogTemp, Log, TEXT("%s attack"), *Character->GetName());
			
			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(NormalAttackDamage, // 데미지 크기
				DamageEvent, // 데미지 종류
				GetController(), // 가해자 (컨트롤러)
				this); // 데미지 전달을 위해 사용한 도구 (액터)

			// 타격 파티클 생성
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), NormalAttackHitParticle, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());
		}
	}
	else
	{
		// No Hit 파티클 생성
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), NormalAttackNoHitParticle, AttackEnd, FRotator::ZeroRotator);
	}
	
	/*FVector MuzzleLocation = GetMesh()->GetSocketLocation(TEXT("Muzzle_01"));
	UParticleSystemComponent* TracerComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), NormalAttackTracerEffect, MuzzleLocation);
	TracerComp->SetVectorParameter()*/
}
void ATwinGunnerCharacter::QSkillCheck()
{
	if (bDied)
		return;

	FHitResult HitResult;
	FVector AttackEnd;

	bool bResult = SweepAttackCheck(HitResult, AttackEnd, AttackRange * 1.5f, AttackRadius);

	if (bResult)
	{
		if (HitResult.Actor.IsValid())
		{
			auto Character = Cast<ACharacter>(HitResult.Actor.Get());
			if (Character == nullptr)
				return;

			UE_LOG(LogTemp, Log, TEXT("%s attack"), *Character->GetName());

			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(QSkillAttackDamage, // 데미지 크기
				DamageEvent, // 데미지 종류
				GetController(), // 가해자 (컨트롤러)
				this); // 데미지 전달을 위해 사용한 도구 (액터)

			// 타격 파티클 생성
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), QSkillHitParticle, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());
		}
	}
	else
	{
		// No Hit 파티클 생성
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), QSkillNoHitParticle, AttackEnd, FRotator::ZeroRotator);
	}
	
}