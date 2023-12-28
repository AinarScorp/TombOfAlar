#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_SetPlayerLocation.generated.h"

UCLASS()
class TEAM09_GP4_API UBTService_SetPlayerLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	UBTService_SetPlayerLocation(){}

	const FName PlayerActorKeyName = "PlayerActor";
	const FName PlayerLocationKeyName = "PlayerLocation";
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
