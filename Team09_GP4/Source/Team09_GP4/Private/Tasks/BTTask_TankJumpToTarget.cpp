#include "Tasks/BTTask_TankJumpToTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UBTTask_TankJumpToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ActorLocation = OwnerComp.GetAIOwner()->GetCharacter()->GetActorLocation();
	TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(BlackboardKey.SelectedKeyName);
	Direction = TargetLocation - ActorLocation;
	TargetLocation.Z -= 100.f;
	
	Direction.X = (Direction.X / JumpDuration);
	Direction.Y = (Direction.Y / JumpDuration);
	Direction.Z = ((TargetLocation.Z - (ActorLocation.Z - (((FMath::Pow(JumpDuration, 2)) * 0.5) * Gravity))) / JumpDuration);

	OwnerComp.GetAIOwner()->GetCharacter()->LaunchCharacter(Direction, false, false);
	return EBTNodeResult::Succeeded;
}
