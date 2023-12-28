#include "Decorators/BTDecorator_LocationInRange.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UBTDecorator_LocationInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const FVector CharacterLocation = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
	const FVector TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(BlackboardKey.SelectedKeyName);
	const float Distance = FVector::Distance(CharacterLocation, TargetLocation);
	if(Distance > MinRange && Distance < MaxRange)
	{
		return true;
	}
	return false;
}

