#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTDecorator_LocationInRange.generated.h"

UCLASS()
class TEAM09_GP4_API UBTDecorator_LocationInRange : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
	UBTDecorator_LocationInRange(){}
	
	UPROPERTY(EditAnywhere)
	float MinRange = 0.f;

	UPROPERTY(EditAnywhere)
	float MaxRange = 0.f;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

};
