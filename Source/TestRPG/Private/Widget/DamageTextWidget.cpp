// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/DamageTextWidget.h"
#include "Components/TextBlock.h"

void UDamageTextWidget::UpdateDamage(FText Damage)
{
	UE_LOG(LogTemp, Log, TEXT("UDamageTextWidget UpdateDamage()"));
	DamageText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Damage")));
	if(DamageText != nullptr)
		DamageText->SetText(Damage);
	else
		UE_LOG(LogTemp, Error, TEXT("UpdateDamage() DamageText is null"));

	
}

void UDamageTextWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UE_LOG(LogTemp, Log, TEXT("UDamageTextWidget NativeConstruct()"));
	DamageText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Damage")));

	if (DamageText == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("NativeConstruct() DamageText is null"));
	}
	UE_LOG(LogTemp, Log, TEXT("UDamageTextWidget NativeConstruct() End"));
}
