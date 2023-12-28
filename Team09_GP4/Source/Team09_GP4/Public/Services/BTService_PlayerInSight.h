#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_PlayerInSight.generated.h"

UCLASS()
class TEAM09_GP4_API UBTService_PlayerInSight : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	UBTService_PlayerInSight(){}

	const FName PlayerLocationKeyName = "PlayerLocation";
	const FName CanAttackKeyName = "CanAttack";
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
