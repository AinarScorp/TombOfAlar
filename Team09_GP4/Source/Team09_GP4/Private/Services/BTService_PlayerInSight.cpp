#include "Services/BTService_PlayerInSight.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Tasks/BTTask_FireShot.h"

void UBTService_PlayerInSight::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FHitResult RV_Hit(ForceInit);

	FCollisionQueryParams CollisionParameters;
	CollisionParameters.AddIgnoredActor(OwnerComp.GetAIOwner()->GetCharacter());

	GetWorld()->LineTraceSingleByChannel(
		RV_Hit,
		OwnerComp.GetAIOwner()->GetCharacter()->GetActorLocation(),
		OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsVector(PlayerLocationKeyName),
		ECC_Visibility,
		CollisionParameters
	);
	if(RV_Hit.GetActor() == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		if(const UBTTask_MoveTo* MoveToNode = Cast<UBTTask_MoveTo>(GetMyNode()))
		{
			MoveToNode->FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
	else
	{
		if(Cast<UBTTask_FireShot>(GetMyNode()))
		{
			OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsBool(CanAttackKeyName, false);
		}
	}
}
