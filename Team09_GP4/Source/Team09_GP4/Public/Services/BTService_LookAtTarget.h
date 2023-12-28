// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_LookAtTarget.generated.h"

/**
 * 
 */
UCLASS()
class TEAM09_GP4_API UBTService_LookAtTarget : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTService_LookAtTarget();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
private:
	FVector GetLookDirection(UBehaviorTreeComponent& OwnerComp) const;
	FRotator GetRotationToDirection(FVector From, FVector To) const;
};
