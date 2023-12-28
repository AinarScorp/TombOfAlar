// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Damageable.generated.h"



UINTERFACE(MinimalAPI, BlueprintType)
class UDamageable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TEAM09_GP4_API IDamageable
{
	GENERATED_BODY()



public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
	void TakeDamage(float damage, FVector HitPoint);

};

