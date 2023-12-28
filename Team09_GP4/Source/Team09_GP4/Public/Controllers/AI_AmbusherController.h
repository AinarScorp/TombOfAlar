// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controllers/AIControllerBase.h"
#include "AI_AmbusherController.generated.h"

class AAI_Ambusher;
/**
 * 
 */
UCLASS()
class TEAM09_GP4_API AAI_AmbusherController : public AAIControllerBase
{
	GENERATED_BODY()
public:
	virtual void OnPossess(APawn* InPawn) override;
	
	virtual void OnUnPossess() override;
	UFUNCTION()
	void StartBehaviourTreeUponNoticingPlayer(AActor* Player);
private:
	UFUNCTION()
	void SetTrueToHasHitPlayerKey();
private:
	UPROPERTY()
	AAI_Ambusher* PossessedAmbusher;
};
