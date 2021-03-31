// Fill out your copyright notice in the Description page of Project Settings.


#include "TwinGunnerCharacter.h"
#include "TPlayerAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATwinGunnerCharacter::ATwinGunnerCharacter()
{
	AttackRange = 500.0f;
	AttackRadius = 50.0f;

	MuzzleSocket = TEXT("Muzzle_01");
	
}

void ATwinGunnerCharacter::BeginPlay()
{
	Super::BeginPlay();

	AnimInstance = Cast<UTPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	if(AnimInstance == nullptr)
		UE_LOG(LogTemp, Error, TEXT("AnimInstance is nullptr"));

	AnimInstance->OnNormalAttackHitCheckDelegate.AddUObject(this, &ATwinGunnerCharacter::NormalAttackCheck);
	AnimInstance->OnNormalAttackEndDelegate.AddUObject(this, &ATwinGunnerCharacter::SetNormalAttackEnd);
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
}

void ATwinGunnerCharacter::NormalAttack()
{
	if (bNormalAttack)
		return;
	if (AnimInstance != nullptr)
	{
		AnimInstance->PlayNormalAttack();
		bNormalAttack = true;
		GetWorldTimerManager().SetTimer(NormalAttackTimer, this, &ATwinGunnerCharacter::SetNormalAttackEnd, NormalAttackCoolTime, false);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("AnimInstance is nullptr"));
	
}

void ATwinGunnerCharacter::Shift()
{
	if (AnimInstance != nullptr)
		AnimInstance->PlayShift();
	else
		UE_LOG(LogTemp, Error, TEXT("AnimInstance is nullptr"));

	//GetCharacterMovement()->
	float Velocity = 900.0f; // 순간 속도
	GetCharacterMovement()->Velocity = GetActorForwardVector() * Velocity;
	Jump();
}

void ATwinGunnerCharacter::NormalAttackCheck()
{
	FHitResult HitResult;

	FCollisionQueryParams Params(NAME_None, false, this);

	//for (TObjectIterator<ANBBaseCharacter> It; It; ++It)
	//{
	//	if ((*It)->GetMyTeam() == MyTeam)
	//	{
	//		Params.AddIgnoredActor(*It);
	//		
	//	}
	//}
	FRotator AttackRot = Controller->GetControlRotation();
	FVector AttackStart;
	GetActorEyesViewPoint(AttackStart, AttackRot);
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
			HitResult.Actor->TakeDamage(10.0f, // 데미지 크기
				DamageEvent, // 데미지 종류
				GetController(), // 가해자 (컨트롤러)
				this); // 데미지 전달을 위해 사용한 도구 (액터)

			// 타격 파티클 생성
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), NormalAttackHitParticle, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());
		}
	}
}
void ATwinGunnerCharacter::SetNormalAttackEnd()
{
	bNormalAttack = false;
}