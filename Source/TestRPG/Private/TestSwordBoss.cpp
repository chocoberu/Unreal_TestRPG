// Fill out your copyright notice in the Description page of Project Settings.


#include "TestSwordBoss.h"
#include "THealthComponent.h"
#include "TEnemyAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "NavigationSystem.h"

ATestSwordBoss::ATestSwordBoss()
{
	bEntrance = true;
	BossPhase = EBossPhase::E_Phase1;
	Phase2Percent = 0.5f;
}

void ATestSwordBoss::BeginPlay()
{
	Super::BeginPlay();
	EnemyAnimInstance = Cast<UTEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	EnemyAnimInstance->OnEntranceStartDelegate.AddUObject(this, &ATestSwordBoss::SetEntranceStart);
	EnemyAnimInstance->OnEntranceEndDelegate.AddUObject(this, &ATestSwordBoss::SetEntranceEnd);
	EnemyAnimInstance->OnNormalAttackHitCheckDelegate.AddUObject(this, &ATestSwordBoss::NormalAttackCheck);
	EnemyAnimInstance->OnUppercutHitCheckDelegate.AddUObject(this, &ATestSwordBoss::UppercutAttackCheck);

	if (EnemyAIController != nullptr)
	{
		EnemyAIController->RunAI();
		auto BlackboardComp = EnemyAIController->GetBlackboardComponent();
		if (BlackboardComp == nullptr)
			return;
		BlackboardComp->SetValueAsBool(TEXT("bEntrance"), true);
		BlackboardComp->SetValueAsEnum(TEXT("BossState"), (uint8)EEnemyState::E_Entrance);
	}
}

void ATestSwordBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATestSwordBoss::OnHealthChangedProcess(float Health)
{
	Super::OnHealthChangedProcess(Health);

	// Phase 2 진입 처리
	if (Health <= HealthComponent->GetDefaultHealth() * Phase2Percent && BossPhase == EBossPhase::E_Phase1)
	{
		BossPhase = EBossPhase::E_Phase2;

		auto BlackboardComp = EnemyAIController->GetBlackboardComponent();
		if (BlackboardComp == nullptr)
			return;
		BlackboardComp->SetValueAsEnum(TEXT("BossPhase"), (uint8)EBossPhase::E_Phase2);

		// TODO : Phase2 능력치 상승 부분 처리
		NormalAttackDamage *= 1.5f;
		GetCharacterMovement()->MaxWalkSpeed = DefaultMaxSpeed * 1.5f;
	}
}

void ATestSwordBoss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATestSwordBoss::NormalAttack()
{
	EnemyAnimInstance->PlayNormalAttackMontage();
}

void ATestSwordBoss::UppercutAttack()
{
	if (bUppercut)
		return;
	EnemyAnimInstance->PlayUppercutAttackMontage();
}

void ATestSwordBoss::SetEntranceStart()
{
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	bEntrance = true;

}

void ATestSwordBoss::SetEntranceEnd()
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultMaxSpeed;
	bEntrance = false;

	if (EnemyAIController != nullptr)
	{
		auto BlackboardComp = EnemyAIController->GetBlackboardComponent();
		if (BlackboardComp == nullptr)
			return;
		BlackboardComp->SetValueAsVector(TEXT("NextPos"), GetActorLocation());
		BlackboardComp->SetValueAsBool(TEXT("bEntrance"), false);
		BlackboardComp->SetValueAsEnum(TEXT("BossState"), (uint8)EEnemyState::E_Idle);
	}
}

void ATestSwordBoss::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

bool ATestSwordBoss::SweepAttackCheck(FHitResult& HitResult, FVector& AttackEnd, float SkillRange, float SkillRadius)
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

	// 공격 판정 범위를 DrawDebugCapsule로 표시
#if ENABLE_DRAW_DEBUG
	FVector TraceVec = GetActorForwardVector() * SkillRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = SkillRadius * 0.5f;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	float DebugLifeTime = 1.0f;

	DrawDebugCapsule(GetWorld(),
		Center,
		HalfHeight,
		SkillRadius,
		AttackRot.Quaternion(),
		DebugColor,
		false,
		DebugLifeTime);
#endif

	return bResult;
}

void ATestSwordBoss::NormalAttackCheck()
{
	if (bDied)
		return;
	UE_LOG(LogTemp, Log, TEXT("SwordBoss : NormalAttackCheck"));
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

			UE_LOG(LogTemp, Log, TEXT("SwordBoss : %s attack"), *Character->GetName());

			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(NormalAttackDamage, // 데미지 크기
				DamageEvent, // 데미지 종류
				GetController(), // 가해자 (컨트롤러)
				this); // 데미지 전달을 위해 사용한 도구 (액터)

			// 타격 파티클 생성
			//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), NormalAttackHitParticle, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());
		}
	}
	else
	{
		// No Hit 파티클 생성
		//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), NormalAttackNoHitParticle, AttackEnd, FRotator::ZeroRotator);
	}
}

void ATestSwordBoss::UppercutAttackCheck()
{
	// TODO : uppercut attack check
	if (bDied)
		return;
	UE_LOG(LogTemp, Log, TEXT("SwordBoss : UppercutCheck"));
	FHitResult HitResult;
	FVector AttackEnd;

	bool bResult = SweepAttackCheck(HitResult, AttackEnd, AttackRange * 1.2f, AttackRadius * 1.2f);
	if (bResult)
	{
		if (HitResult.Actor.IsValid())
		{
			auto Character = Cast<ACharacter>(HitResult.Actor.Get());
			if (Character == nullptr)
				return;

			UE_LOG(LogTemp, Log, TEXT("SwordBoss : %s attack"), *Character->GetName());

			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(UppercutAttackDamage, // 데미지 크기
				DamageEvent, // 데미지 종류
				GetController(), // 가해자 (컨트롤러)
				this); // 데미지 전달을 위해 사용한 도구 (액터)
		}
	}

	bUppercut = true;
	GetWorldTimerManager().SetTimer(UppercutTimer, FTimerDelegate::CreateLambda([&]() {bUppercut = false; }), UppercutCoolTime, false);
}

void ATestSwordBoss::SpawnMinion()
{
	if (bSpawnMinion)
		return;
	EnemyAnimInstance->PlaySpawnMontage();
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FNavLocation NextLocation;

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (NavSystem == nullptr)
		return;

	if (NavSystem->GetRandomPointInNavigableRadius(GetActorLocation(), 600.0f, NextLocation))
	{
		FVector Location = NextLocation.Location;
		Location.Z = GetActorLocation().Z + 50.0f;
		ATBaseEnemyCharacter* Minion = GetWorld()->SpawnActor<ATBaseEnemyCharacter>(MinionClass, Location, FRotator::ZeroRotator, SpawnParams);
		Minion->SetOwner(this);
	}

	bSpawnMinion = true;
	GetWorldTimerManager().SetTimer(SpawnTimer, FTimerDelegate::CreateLambda([&]() {bSpawnMinion = false; }), SpawnCoolTime, false);

}
bool ATestSwordBoss::CanUppercut()
{
	return !bUppercut;
}