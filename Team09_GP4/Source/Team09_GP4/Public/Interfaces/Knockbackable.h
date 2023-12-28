// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Knockbackable.generated.h"


UINTERFACE(MinimalAPI, BlueprintType)
class UKnockbackable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TEAM09_GP4_API IKnockbackable
{
	GENERATED_BODY()

	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Knockback")
	void ApplyKnockback(float force, FVector direction, AActor* scource = nullptr);
};
