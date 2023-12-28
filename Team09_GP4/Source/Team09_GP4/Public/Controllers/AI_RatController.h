// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controllers/AIControllerBase.h"
#include "AI_RatController.generated.h"

/**
 * 
 */
UCLASS()
class TEAM09_GP4_API AAI_RatController : public AAIControllerBase
{
	GENERATED_BODY()
public:
	virtual void OnPossess(APawn* InPawn) override;


};
