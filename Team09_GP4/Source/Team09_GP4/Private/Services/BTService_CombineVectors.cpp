// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/BTService_CombineVectors.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Library/EinarMathLibrary.h"


UBTService_CombineVectors::UBTService_CombineVectors()
{
	NodeName = "CombineVectors";
	Interval = 0.001;
	RandomDeviation = 0;
	KeyToAssignInto.AddVectorFilter(this,GET_MEMBER_NAME_CHECKED(UBTService_CombineVectors,KeyToAssignInto));
	
}

void UBTService_CombineVectors::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
	UBlackboardData* BBAsset = GetBlackboardAsset();

	if (!ensure(BBAsset)) return;
	KeyToAssignInto.ResolveSelectedKey(*BBAsset);

	for (auto& Vector : VectorsToCombine)
	{
		Vector.BlackboardKey.ResolveSelectedKey(*BBAsset);
	}
}

void UBTService_CombineVectors::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(KeyToAssignInto.SelectedKeyName,CombineVectors(OwnerComp));
}

FVector UBTService_CombineVectors::CombineVectors(UBehaviorTreeComponent& OwnerComp)
{
	const FVector ControlledPawnLocation = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
	FVector CombinedVector = AddPawnLocation? ControlledPawnLocation: FVector::ZeroVector;
	
	for (auto& [Add_X, Add_Y, Add_Z, AddDirectionOnly, BlackboardKey] : VectorsToCombine)
	{
		const FVector BlackboardKeyVector = GetVectorFromBlackboardKey(OwnerComp, BlackboardKey);
		FVector VectorToAdd;
		if (AddDirectionOnly)
		{
			float VectorLength;
			UEinarMathLibrary::DirectionToVector(ControlledPawnLocation,BlackboardKeyVector,false, VectorToAdd, VectorLength);
		}
		else
		{
			VectorToAdd = BlackboardKeyVector;
		}
		VectorToAdd.X = Add_X? VectorToAdd.X: 0.f;
		VectorToAdd.Y = Add_Y? VectorToAdd.Y: 0.f;
		VectorToAdd.Z = Add_Z? VectorToAdd.Z: 0.f;
		CombinedVector+=VectorToAdd;
	}
	VisualiseCombinedVector(ControlledPawnLocation,CombinedVector);
	return CombinedVector;
}

FVector UBTService_CombineVectors::GetVectorFromBlackboardKey(UBehaviorTreeComponent& OwnerComp, FBlackboardKeySelector& Key)
{
	if (Key.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
	{
		return OwnerComp.GetBlackboardComponent()->GetValueAsVector(Key.SelectedKeyName);
	}
	if (Key.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
	{
		if (const AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(Key.SelectedKeyName)))
		{
			return TargetActor->GetActorLocation();
		}
	}
	return FVector::ZeroVector;
}

void UBTService_CombineVectors::VisualiseCombinedVector(const FVector& PawnLocation, const FVector& CombinedVector) const
{
	if (!DrawCombinedVector) return;
	UKismetSystemLibrary::DrawDebugArrow(GetWorld(),PawnLocation, CombinedVector,2.f,FLinearColor::Red,0.05,1.f);

}
