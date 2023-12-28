#include "Decorators/BTDecorator_CheckBoolValue.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "AIController.h"

bool UBTDecorator_CheckBoolValue::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	return OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsBool(BlackboardKey.SelectedKeyName);
}
