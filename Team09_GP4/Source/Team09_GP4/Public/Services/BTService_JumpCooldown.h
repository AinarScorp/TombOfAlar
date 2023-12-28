#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_JumpCooldown.generated.h"

UCLASS()
class TEAM09_GP4_API UBTService_JumpCooldown : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	UBTService_JumpCooldown(){}

	float CooldownTimer = 0.f;
	
	const FName CanJumpKeyName = "CanJump";
	const FName JumpCooldownKeyName = "JumpCooldown";
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
