#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Particles/ParticleSystem.h"

#include "BTTask_TankJumpToTarget.generated.h"

UCLASS()
class TEAM09_GP4_API UBTTask_TankJumpToTarget : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	UBTTask_TankJumpToTarget(){}
	
	UPROPERTY(EditAnywhere)
	float JumpDuration = 1.5f;
	
	const float Gravity = 980.f;

	FVector ActorLocation;
	FVector TargetLocation;
	FVector Direction;

	float Distance = 0.f;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
