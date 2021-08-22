// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/BloodOverlayHUDWidget.h"
#include "THealthComponent.h"
#include "Components/Image.h"


void UBloodOverlayHUDWidget::UpdateHUDWidget(float HPRatio)
{
	if (OverlayHUD != nullptr)
	{
		float Percent = FMath::Clamp<float>(1.0f - HPRatio, 0.0f, 1.0f);
		
		// ShowPercent ���� ���� ��ġ�̸� HUD ������ �ʵ��� ����
		Percent = Percent >= ShowPercent ? Percent : 0.0f; 

		FLinearColor HUDColor = FLinearColor(1.0f, 1.0f, 1.0f, Percent);
		OverlayHUD->SetColorAndOpacity(HUDColor);
	}
}

void UBloodOverlayHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OverlayHUD = Cast<UImage>(GetWidgetFromName(TEXT("IMG_BloodOverlay")));
	if (OverlayHUD != nullptr)
		UpdateHUDWidget(1.0f);
}
