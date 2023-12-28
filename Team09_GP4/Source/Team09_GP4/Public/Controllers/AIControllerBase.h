// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIControllerBase.generated.h"

class AEnemyBase;

UENUM(BlueprintType)
enum class EEnemyBlackboardKeys : uint8
{
	EEBK_TargetToMove UMETA(DisplayName = "TargetToMove"),
	EEBK_Destination UMETA(DisplayName = "Destination"),
	EEBK_IsAttacking UMETA(DisplayName = "IsAttacking"),
	EEBK_IsSlowingPlayer UMETA(DisplayName = "IsSlowingPlayer"),
	EEBK_HasHitPlayer UMETA(DisplayName = "HasHitPlayer"),
	EEBK_AnimationIsPlaying UMETA(DisplayName = "AnimationIsPlaying")
};
/**
 * 
 */
UCLASS()
class TEAM09_GP4_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()
public:
	virtual void OnPossess(APawn* InPawn) override;
	UFUNCTION()
	void SetFalseToAnimationIsPlayingKey();
protected:
	FName GetEnemyBlackboardKey(EEnemyBlackboardKeys BlackboardKey);
};
