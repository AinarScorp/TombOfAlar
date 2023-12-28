// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/BTService_LookAtTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Kismet/KismetMathLibrary.h"

UBTService_LookAtTarget::UBTService_LookAtTarget()
{

	NodeName = "LookAtTarget";
	Interval = 0.001;
	RandomDeviation = 0;
	BlackboardKey.AddVectorFilter(this,GET_MEMBER_NAME_CHECKED(UBTService_LookAtTarget,BlackboardKey));
	BlackboardKey.AddObjectFilter(this,GET_MEMBER_NAME_CHECKED(UBTService_LookAtTarget,BlackboardKey),AActor::StaticClass());
}



void UBTService_LookAtTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const FVector ActorLocation = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
	OwnerComp.GetAIOwner()->GetPawn()->SetActorRotation(GetRotationToDirection(ActorLocation, GetLookDirection(OwnerComp)));
}

FVector UBTService_LookAtTarget::GetLookDirection(UBehaviorTreeComponent& OwnerComp) const
{
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
	{
		return OwnerComp.GetBlackboardComponent()->GetValueAsVector(BlackboardKey.SelectedKeyName);
	}
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
	{
		if (const AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName)))
		{
			return  TargetActor->GetActorLocation();
		}
	}
	return FVector::ZeroVector;
}

FRotator UBTService_LookAtTarget::GetRotationToDirection(FVector From, FVector To) const
{
	const FVector Up{0,0,1};
	const FVector Forward = UKismetMathLibrary::ProjectVectorOnToPlane(UKismetMathLibrary::GetDirectionUnitVector(From,To), Up);
	const FVector Right = UKismetMathLibrary::Cross_VectorVector(Up,Forward);
	return UKismetMathLibrary::MakeRotationFromAxes(Forward,Right,Up);
}
