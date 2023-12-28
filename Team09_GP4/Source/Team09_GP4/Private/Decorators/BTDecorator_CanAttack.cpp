// Fill out your copyright notice in the Description page of Project Settings.


#include "Decorators/BTDecorator_CanAttack.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Library/EinarMathLibrary.h"

UBTDecorator_CanAttack::UBTDecorator_CanAttack()
{
	//INIT_DECORATOR_NODE_NOTIFY_FLAGS();
	//bNotifyTick = true;
	AttackTarget.AddVectorFilter(this,GET_MEMBER_NAME_CHECKED(UBTDecorator_CanAttack,AttackTarget));
	AttackTarget.AddObjectFilter(this,GET_MEMBER_NAME_CHECKED(UBTDecorator_CanAttack,AttackTarget),AActor::StaticClass());
}

void UBTDecorator_CanAttack::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
	UBlackboardData* BBAsset = GetBlackboardAsset();
	if (BBAsset)
	{
		AttackTarget.ResolveSelectedKey(*BBAsset);
	}
	else
	{
		AttackTarget.InvalidateResolvedKey();
	}
}

void UBTDecorator_CanAttack::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	OwnerComp.RequestExecution(this);
	if (!DrawDebugLine) return;
	const APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	UKismetSystemLibrary::DrawDebugCone(GetWorld(),Pawn->GetActorLocation() + LocationOffset,Pawn->GetActorForwardVector(),
		AttackRadius,VisionAttackAngle*0.5f,2,12,FLinearColor::Yellow,.1f,2.f);
}

bool UBTDecorator_CanAttack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	FVector AttackTargetLocation{0};
	if (AttackTarget.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
	{
		AttackTargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AttackTarget.SelectedKeyName);
	}
	else if (AttackTarget.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
	{
		if (const AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AttackTarget.SelectedKeyName)))
		{
			AttackTargetLocation = TargetActor->GetActorLocation();
		}
	}
	const APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	const FVector FromVector = Pawn->GetActorLocation() + LocationOffset;
	FVector DirectionVector;
	float VectorLength;
	UEinarMathLibrary::DirectionToVector(FromVector, AttackTargetLocation, false, DirectionVector,VectorLength);
	const float Angle = UEinarMathLibrary::GetAngleBetweenVectors(Pawn->GetActorForwardVector(),DirectionVector);
	return VectorLength<=AttackRadius && Angle <= VisionAttackAngle*0.5f;
	
}
