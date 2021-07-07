// Fill out your copyright notice in the Description page of Project Settings.


#include "TestSwordBoss.h"
#include "THealthComponent.h"
#include "TEnemyAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "NavigationSystem.h"
#include "TestSlash.h"

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
	EnemyAnimInstance->OnUppercutRotateDelegate.AddUObject(this, &ATestSwordBoss::RotateToTarget);
	EnemyAnimInstance->OnMontageEnded.AddDynamic(this, &ATBaseEnemyCharacter::OnAttackEnded);

	if (EnemyAIController != nullptr)
	{
		EnemyAIController->RunAI();
		BlackboardComp = EnemyAIController->GetBlackboardComponent();
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

void ATestSwordBoss::OnHealthChangedProcess(float Health, float Damage)
{
	Super::OnHealthChangedProcess(Health, Damage);

	// Phase 2 진입 처리
	if (Health <= HealthComponent->GetDefaultHealth() * Phase2Percent && BossPhase == EBossPhase::E_Phase1)
	{
		BossPhase = EBossPhase::E_Phase2;

		//auto BlackboardComp = EnemyAIController->GetBlackboardComponent();
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
		//auto BlackboardComp = EnemyAIController->GetBlackboardComponent();
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

bool ATestSwordBoss::SweepMultiAttackCheck(TArray<FHitResult>& OutHits, FVector& AttackEnd, float SkillRange, float SkillRadius)
{
	FCollisionQueryParams Params(NAME_None, false, this);

	FRotator AttackRot;
	FVector AttackStart;
	GetActorEyesViewPoint(AttackStart, AttackRot);
	AttackEnd = AttackStart + AttackRot.Vector() * SkillRange;

	bool bResult = GetWorld()->SweepMultiByChannel(
		OutHits,
		AttackStart,
		AttackEnd,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeCapsule(SkillRadius, SkillRange * 0.5f),
		Params);

	// Debug 관련
	FColor DebugColor = bResult ? FColor::Green : FColor::Red;
	DrawDebugLine(GetWorld(), AttackStart, AttackEnd, DebugColor, false, 1.0f);

	// 공격 판정 범위를 DrawDebugCapsule로 표시
#if ENABLE_DRAW_DEBUG
	FVector TraceVec = GetActorForwardVector() * SkillRange;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = SkillRange * 0.5f;
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
	
	TArray<FHitResult> OutHits;

	FVector AttackEnd;

	bool bResult = SweepMultiAttackCheck(OutHits, AttackEnd, AttackRange, AttackRadius);

	if (bResult)
	{
		for (auto& iter : OutHits)
		{
			if (!iter.Actor.IsValid())
				continue;
			auto Character = Cast<ACharacter>(iter.Actor.Get());
			if (Character == nullptr)
				continue;
			
			UE_LOG(LogTemp, Log, TEXT("SwordBoss : %s attack"), *Character->GetName());

			FDamageEvent DamageEvent;
			Character->TakeDamage(NormalAttackDamage, // 데미지 크기
				DamageEvent, // 데미지 종류
				GetController(), // 가해자 (컨트롤러)
				this); // 데미지 전달을 위해 사용한 도구 (액터)
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
	if (bDied)
		return;
	UE_LOG(LogTemp, Log, TEXT("SwordBoss : UppercutCheck"));
	TArray<FHitResult> OutHits;
	FVector AttackEnd;

	bool bResult = SweepMultiAttackCheck(OutHits, AttackEnd, AttackRange, AttackRadius);

	if (bResult)
	{
		for (auto& iter : OutHits)
		{
			if (!iter.Actor.IsValid())
				continue;

			auto Character = Cast<ACharacter>(iter.Actor.Get());
			if (Character == nullptr)
				continue;

			FDamageEvent DamageEvent;
			Character->TakeDamage(UppercutAttackDamage, // 데미지 크기
				DamageEvent, // 데미지 종류
				GetController(), // 가해자 (컨트롤러)
				this); // 데미지 전달을 위해 사용한 도구 (액터)

		}
	}

	// Slash 
	FVector SlashDir = Cast<ACharacter>(BlackboardComp->GetValueAsObject(TEXT("TargetActor")))->GetActorLocation() - GetActorLocation();
	SlashDir = SlashDir / SlashDir.Size();
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	auto Slash = GetWorld()->SpawnActor<ATestSlash>(SlashClass, GetActorLocation() + GetActorForwardVector() * 300.0f, GetActorRotation(), SpawnParams);

	if (Slash)
	{
		Slash->SetOwner(this);
		//Slash->SetSlashDirection(GetActorForwardVector());
		Slash->SetSlashDirection(SlashDir);
	}

	bUppercut = true;
	GetWorldTimerManager().SetTimer(UppercutTimer, FTimerDelegate::CreateLambda([&]() {bUppercut = false; }), UppercutCoolTime, false);
}

void ATestSwordBoss::RotateToTarget()
{
	if (bDied)
		return;

	auto Character = Cast<ACharacter>(BlackboardComp->GetValueAsObject(TEXT("TargetActor")));
	if (Character == nullptr)
		return;

	FVector Forward = Character->GetActorLocation() - GetActorLocation();
	Forward.Z = 0.0f;
	
	// TEST CODE
	SetActorRotation(Forward.Rotation());
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

bool ATestSwordBoss::CanSpawn()
{
	return !bSpawnMinion;
}