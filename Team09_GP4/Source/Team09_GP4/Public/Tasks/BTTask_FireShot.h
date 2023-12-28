#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FireShot.generated.h"

UCLASS()
class TEAM09_GP4_API UBTTask_FireShot : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	UBTTask_FireShot(){}
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
