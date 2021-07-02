// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamageTextWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTRPG_API UDamageTextWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void UpdateDamage(FText Damage);

protected:
	virtual void NativeConstruct() override;

private:

	UPROPERTY()
	class UTextBlock* DamageText;
};
