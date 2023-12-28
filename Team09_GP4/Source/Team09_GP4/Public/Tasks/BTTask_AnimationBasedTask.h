// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_AnimationBasedTask.generated.h"

/**
 * 
 */
UCLASS()
class TEAM09_GP4_API UBTTask_AnimationBasedTask : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_AnimationBasedTask();
protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	void SetBlackboardKeyToTrue(UBehaviorTreeComponent& OwnerComp) const;
protected:
	UPROPERTY(EditAnywhere, Category=Blackboard)
	FBlackboardKeySelector AnimationIsPlayingBool;
};
