#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SetBoolValue.generated.h"

UCLASS()
class TEAM09_GP4_API UBTTask_SetBoolValue : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	UBTTask_SetBoolValue() {}
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere)
	bool BoolValue = false;
};
