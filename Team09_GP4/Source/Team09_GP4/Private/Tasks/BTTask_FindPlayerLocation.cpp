#include "Tasks/BTTask_FindPlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UBTTask_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const FVector PlayerLocation = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();
	if(FNavigationSystem::IsValidLocation(PlayerLocation))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, PlayerLocation);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
