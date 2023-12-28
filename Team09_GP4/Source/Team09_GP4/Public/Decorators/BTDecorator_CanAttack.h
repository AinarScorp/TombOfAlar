// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CanAttack.generated.h"

/**
 * 
 */
UCLASS()
class TEAM09_GP4_API UBTDecorator_CanAttack : public UBTDecorator
{
	GENERATED_BODY()
public:
	UBTDecorator_CanAttack();
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
protected:
	UPROPERTY(EditAnywhere, Category=Blackboard)
	FBlackboardKeySelector AttackTarget;
private:
	UPROPERTY(EditAnywhere, Category="Settings")
	float AttackRadius = 50.f;
	UPROPERTY(EditAnywhere, Category="Settings")
	float VisionAttackAngle = 90.f;
	UPROPERTY(EditAnywhere, Category="Settings")
	FVector LocationOffset;
	UPROPERTY(EditAnywhere, Category="Debug")
	bool DrawDebugLine = false;
};
