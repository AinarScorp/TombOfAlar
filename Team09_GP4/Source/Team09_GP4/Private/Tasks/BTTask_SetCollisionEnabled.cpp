#include "Tasks/BTTask_SetCollisionEnabled.h"

#include "AIController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GeometryCollection/GeometryCollectionSimulationTypes.h"

EBTNodeResult::Type UBTTask_SetCollisionEnabled::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UCapsuleComponent* CapsuleComponent = OwnerComp.GetAIOwner()->GetCharacter()->GetCapsuleComponent();
	if(!BoolValue)
	{
		CapsuleComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel5, ECR_Ignore);
	}
	else
	{
		CapsuleComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel5, ECR_Block);
	}
	return EBTNodeResult::Succeeded;
}
