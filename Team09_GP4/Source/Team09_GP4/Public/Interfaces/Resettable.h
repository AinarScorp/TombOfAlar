// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Resettable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UResettable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TEAM09_GP4_API IResettable
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	AActor* GetActor();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ResetUponPlayerDeath();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void LockReset(bool DeactivateReset);
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
