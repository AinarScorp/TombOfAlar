#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTDecorator_CheckBoolValue.generated.h"

UCLASS()
class TEAM09_GP4_API UBTDecorator_CheckBoolValue : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
	UBTDecorator_CheckBoolValue(){}
	
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

};
