// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enemy.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemy : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TEAM09_GP4_API IEnemy
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "IEnemy")
	bool PerformAttack();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "IEnemy")
	bool AnimationHasFinished();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "IEnemy")
	bool ToggleAttackExecution(bool TurnOn);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "IEnemy")
	bool ReplaceWithCorpse();
	
	
};
