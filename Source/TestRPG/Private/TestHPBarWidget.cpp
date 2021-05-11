// Fill out your copyright notice in the Description page of Project Settings.


#include "TestHPBarWidget.h"
#include "THealthComponent.h"
#include "Components/ProgressBar.h"

void UTestHPBarWidget::BindCharacter(UTHealthComponent* NewCharacterComp)
{
	if (NewCharacterComp != nullptr)
	{
		HealthComp = NewCharacterComp;

		//HealthComp->OnHealthChanged.AddUObject(this, &UTestHPBarWidget::UpdateHPWidget);
	}
}

void UTestHPBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	if (HPProgressBar != nullptr)
		UpdateHPWidget();
}

void UTestHPBarWidget::UpdateHPWidget()
{
	if (HealthComp != nullptr && HPProgressBar != nullptr)
	{
		HPProgressBar->SetPercent(HealthComp->GetHPRatio());
	}
}
