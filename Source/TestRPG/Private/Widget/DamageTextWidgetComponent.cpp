// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/DamageTextWidgetComponent.h"
#include "Widget/DamageTextWidget.h"

void UDamageTextWidgetComponent::SetDamageText(float Damage)
{
	auto DamageTextObject = Cast<UDamageTextWidget>(GetUserWidgetObject());

	if (DamageTextObject == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Error : DamageText Object is null"));
		return;
	}

	FText Text = FText::FromString(FString::SanitizeFloat(Damage));
	DamageTextObject->UpdateDamage(Text);

	FTimerHandle DestroyHandle;

	GetWorld()->GetTimerManager().SetTimer(DestroyHandle, FTimerDelegate::CreateLambda([&]() {
		DestroyComponent();
		}), 2.0f, false);
}