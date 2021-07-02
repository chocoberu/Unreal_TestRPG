// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/DamageTextWidget.h"
#include "Components/TextBlock.h"

void UDamageTextWidget::UpdateDamage(FText Damage)
{
	DamageText->SetText(Damage);
}

void UDamageTextWidget::NativeConstruct()
{
	Super::NativeConstruct();

	DamageText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Damage")));
}
