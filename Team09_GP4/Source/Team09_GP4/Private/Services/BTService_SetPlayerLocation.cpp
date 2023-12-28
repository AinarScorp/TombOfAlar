#include "Services/BTService_SetPlayerLocation.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

void UBTService_SetPlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsObject(PlayerActorKeyName,
	UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsVector(PlayerLocationKeyName,
		UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation());
}
