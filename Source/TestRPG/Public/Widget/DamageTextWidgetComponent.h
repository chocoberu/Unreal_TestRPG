// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "DamageTextWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class TESTRPG_API UDamageTextWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	void SetDamageText(float Damage);
};
