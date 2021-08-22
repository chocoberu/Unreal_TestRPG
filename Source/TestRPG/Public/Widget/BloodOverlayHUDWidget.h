// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BloodOverlayHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTRPG_API UBloodOverlayHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	void UpdateHUDWidget(float HPRatio);

protected:

	virtual void NativeConstruct() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	float ShowPercent;

private:
	
	UPROPERTY()
	class UImage* OverlayHUD;

	
};
