// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/BloodOverlayHUDWidget.h"
#include "THealthComponent.h"
#include "Components/Image.h"


void UBloodOverlayHUDWidget::UpdateHUDWidget(float HPRatio)
{
	if (OverlayHUD != nullptr)
	{
		GetWorld()->GetTimerManager().ClearTimer(InvisibleHUDTimer);
		float Percent = FMath::Clamp<float>(1.0f - HPRatio, 0.0f, 1.0f);
		
		// ShowPercent 보다 작은 수치이면 HUD 보이지 않도록 설정
		//Percent = Percent >= ShowPercent ? Percent : 0.0f; 

		FLinearColor HUDColor = FLinearColor(1.0f, 1.0f, 1.0f, Percent);
		OverlayHUD->SetColorAndOpacity(HUDColor);

		GetWorld()->GetTimerManager().SetTimer(InvisibleHUDTimer, FTimerDelegate::CreateLambda([&]() {
			FLinearColor InvisbleColor = FLinearColor(1.0f, 1.0f, 1.0f, 0.0f);
			OverlayHUD->SetColorAndOpacity(InvisbleColor);
			}), ShowTime, false);
	}
}

void UBloodOverlayHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OverlayHUD = Cast<UImage>(GetWidgetFromName(TEXT("IMG_BloodOverlay")));
	if (OverlayHUD != nullptr)
		UpdateHUDWidget(1.0f);
}
