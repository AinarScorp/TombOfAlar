// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/BTService_AddSeparationForce.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Library/EinarMathLibrary.h"
#include "Subsystems/EnemyHordeSubsystem.h"

UBTService_AddSeparationForce::UBTService_AddSeparationForce()
{
	NodeName = "Add Separation Force";
	Interval = 0.001;
	RandomDeviation = 0;
	BlackboardKey.AddVectorFilter(this,GET_MEMBER_NAME_CHECKED(UBTService_AddSeparationForce,BlackboardKey));
	
	MoveLocation.AddVectorFilter(this,GET_MEMBER_NAME_CHECKED(UBTService_AddSeparationForce,MoveLocation));
	MoveLocation.AddObjectFilter(this,GET_MEMBER_NAME_CHECKED(UBTService_AddSeparationForce,MoveLocation),AActor::StaticClass());
}
void UBTService_AddSeparationForce::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
	const UBlackboardData* BBAsset = GetBlackboardAsset();
	if (ensure(BBAsset))
	{
		MoveLocation.ResolveSelectedKey(*BBAsset);
	}
}
void UBTService_AddSeparationForce::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	const FVector SeparationForce = CalculateSeparationForce(OwnerComp);
	const APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	VisualisePersonalSpace(Pawn->GetActorLocation(),Pawn->GetActorForwardVector());
	VisualisePersonalSpace(Pawn->GetActorLocation());
	VisualiseSeparationForce(Pawn->GetActorLocation(),SeparationForce);
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName,SeparationForce);
	
}



FVector UBTService_AddSeparationForce::CalculateSeparationForce(UBehaviorTreeComponent& OwnerComp) const
{
	FVector SeparationForce;
	const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	UEnemyHordeSubsystem* EnemySubsystem = GameInstance->GetSubsystem<UEnemyHordeSubsystem>();
	
	if (!EnemySubsystem) return SeparationForce;

	AActor* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	for (AActor* Enemy : EnemySubsystem->ListOfEnemies)
	{
		if (!ShouldApplyForceFromEnemy(ControlledPawn,Enemy)) continue; 
		
		SeparationForce+= GetSeparationForceFromNeighbour(ControlledPawn,Enemy,GetWeightPercent(OwnerComp));
	}
	return SeparationForce;
	
}

FVector UBTService_AddSeparationForce::GetSeparationForceFromNeighbour(AActor* ControlledPawn, AActor* Actor, const float WeightPercent) const
{
	FVector DirectionToNeighbour;
	float VectorLength;
	UEinarMathLibrary::DirectionToActor(Actor,ControlledPawn,true,DirectionToNeighbour, VectorLength);

	const FVector PawnVectorBack = ControlledPawn->GetActorForwardVector() * -1;
	const float Angle = UEinarMathLibrary::GetAngleBetweenVectors(PawnVectorBack,DirectionToNeighbour);
	FVector SeparationForce; 
	if (Angle < AngleThreshold)
	{
		const float Dot = UKismetMathLibrary::Dot_VectorVector(DirectionToNeighbour,ControlledPawn->GetActorRightVector());
		SeparationForce = ControlledPawn->GetActorRightVector() * UKismetMathLibrary::SignOfFloat(Dot);
	}
	else
	{
		SeparationForce = DirectionToNeighbour;
	}
	const float StrengthPercent =  1 -VectorLength / PersonalSpaceRadius;
	return SeparationForce * StrengthPercent * SeparationStrength * WeightPercent;
}



bool UBTService_AddSeparationForce::ShouldApplyForceFromEnemy(AActor* ControlledPawn,AActor* Actor) const
{
	if (ControlledPawn ==  Actor) return false;
	
	FVector DirectionVector;
	float VectorLength;
	UEinarMathLibrary::DirectionToActor(ControlledPawn,Actor,false,DirectionVector, VectorLength);
	
	if (PersonalSpaceRadius < VectorLength) return false;
	
	return UEinarMathLibrary::GetAngleBetweenVectors(DirectionVector,ControlledPawn->GetActorForwardVector()) < AcceptanceAngle;
	
}

float UBTService_AddSeparationForce::GetWeightPercent(UBehaviorTreeComponent& OwnerComp) const
{
	if (!UseWeight) return 1.f;

	FVector MoveLocationVector{0};
	if (MoveLocation.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
	{
		MoveLocationVector=  OwnerComp.GetBlackboardComponent()->GetValueAsVector(MoveLocation.SelectedKeyName);
	}
	else if (MoveLocation.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
	{
		if (const AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(MoveLocation.SelectedKeyName)))
		{
			MoveLocationVector = TargetActor->GetActorLocation();
		}
	}
	VisualiseMoveLocationRadius(MoveLocationVector);
	FVector OutVector;
	float VectorLength;
	UEinarMathLibrary::DirectionToVector(OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation(), MoveLocationVector,false,OutVector,VectorLength);
	return  VectorLength<AcceptanceRadiusForMoveLocation? VectorLength/AcceptanceRadiusForMoveLocation: 1.f;
	
}

void UBTService_AddSeparationForce::VisualiseSeparationForce(const FVector& PawnLocation, const FVector& SeparationForce) const
{
	if (!Gizmos.DrawSeparationForce) return;
	UKismetSystemLibrary::DrawDebugArrow(GetWorld(),PawnLocation, PawnLocation + SeparationForce,2.f,Gizmos.SeparationForceColor,0.05,1.f);
}

void UBTService_AddSeparationForce::VisualiseMoveLocationRadius(const FVector& TargetMoveLocation) const
{
	if (!Gizmos.DrawMoveLocation) return;
	UKismetSystemLibrary::DrawDebugSphere(GetWorld(),TargetMoveLocation, AcceptanceRadiusForMoveLocation,12.f,Gizmos.MoveLocationColor,0.05,1.f);

}

void UBTService_AddSeparationForce::VisualisePersonalSpace(const FVector& PawnLocation) const
{
	if (!Gizmos.DrawPersonalSpace) return;
	UKismetSystemLibrary::DrawDebugSphere(GetWorld(),PawnLocation, PersonalSpaceRadius,12.f,Gizmos.PersonalSpaceColor,0.05,1.f);

}

void UBTService_AddSeparationForce::VisualisePersonalSpace(const FVector& PawnLocation, const FVector& PawnForward) const
{
	if (!Gizmos.DrawAcceptanceAngle) return;
	UKismetSystemLibrary::DrawDebugCone(GetWorld(),PawnLocation,PawnForward, PersonalSpaceRadius,AcceptanceAngle,0,12,Gizmos.AngleColor,0.05,1.f);

}
