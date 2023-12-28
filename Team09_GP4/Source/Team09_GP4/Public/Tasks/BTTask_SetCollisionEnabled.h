#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SetCollisionEnabled.generated.h"

UCLASS()
class TEAM09_GP4_API UBTTask_SetCollisionEnabled : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	UBTTask_SetCollisionEnabled() {}

	UPROPERTY(EditAnywhere)
	bool BoolValue = false;
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
