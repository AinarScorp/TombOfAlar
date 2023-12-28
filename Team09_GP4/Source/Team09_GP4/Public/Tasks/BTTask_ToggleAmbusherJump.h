// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTTask_AnimationBasedTask.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ToggleAmbusherJump.generated.h"

/**
 * 
 */
UCLASS()
class TEAM09_GP4_API UBTTask_ToggleAmbusherJump : public UBTTask_AnimationBasedTask
{
	GENERATED_BODY()
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
private:
	UPROPERTY(EditAnywhere, Category="Settings")
	bool Disappear;
};
