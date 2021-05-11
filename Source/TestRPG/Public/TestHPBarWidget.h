// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestHPBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTRPG_API UTestHPBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void BindCharacter(class UTHealthComponent* NewCharacterComp);

	void UpdateHPWidget();

protected:
	virtual void NativeConstruct() override;

private:
	class UTHealthComponent* HealthComp;

	UPROPERTY()
	class UProgressBar* HPProgressBar;
};
