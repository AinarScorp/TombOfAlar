// Fill out your copyright notice in the Description page of Project Settings.
#include "Services/BTService_PlayerIsAttackable.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Tasks/BTTask_FireShot.h"

void UBTService_PlayerIsAttackable::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* MyController = OwnerComp.GetAIOwner();
	const FVector ActorLocation = MyController->GetCharacter()->GetActorLocation();
	const FVector TargetLocation = MyController->GetBlackboardComponent()->GetValueAsVector(PlayerLocationKeyName);
	const float Distance = FVector::Distance(ActorLocation, TargetLocation);
	
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
	if(Cast<UBTTask_FireShot>(GetMyNode()))
	{
		if(RV_Hit.GetActor() != MyController->GetBlackboardComponent()->GetValueAsObject(PlayerActorKeyName) ||
			Distance > MaxRangeFromTarget)
		{
			OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsBool(CanAttackKeyName, false);
		}
	}
	else if(const UBTTask_MoveTo* MoveToNode = Cast<UBTTask_MoveTo>(GetMyNode()))
	{
		if(RV_Hit.GetActor() == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0) &&
			Distance > MinRangeFromTarget && Distance < MaxRangeFromTarget)
		{
			MoveToNode->FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}
