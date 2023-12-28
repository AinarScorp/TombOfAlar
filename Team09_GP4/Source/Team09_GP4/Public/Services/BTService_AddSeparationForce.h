// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_AddSeparationForce.generated.h"

USTRUCT()
struct FDebugGizmos
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Gizmos|SeparationForce")
	bool DrawSeparationForce;
	UPROPERTY(EditAnywhere, Category = "Gizmos|SeparationForce")
	FLinearColor SeparationForceColor = FLinearColor::Yellow;
	UPROPERTY(EditAnywhere, Category = "Gizmos|AcceptanceAngle")
	bool DrawAcceptanceAngle;
	UPROPERTY(EditAnywhere, Category = "Gizmos|AcceptanceAngle")
	FLinearColor AngleColor = FLinearColor::Blue;
	UPROPERTY(EditAnywhere, Category =  "Gizmos|PersonalSpace")
	bool DrawPersonalSpace;
	UPROPERTY(EditAnywhere, Category =  "Gizmos|PersonalSpace")
	FLinearColor PersonalSpaceColor = FLinearColor::Green;
	UPROPERTY(EditAnywhere, Category =  "Gizmos|Weight")
	bool DrawMoveLocation;
	UPROPERTY(EditAnywhere, Category =  "Gizmos|Weight")
	FLinearColor MoveLocationColor = FLinearColor::Red;
};
/**
 * 
 */
UCLASS()
class TEAM09_GP4_API UBTService_AddSeparationForce : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTService_AddSeparationForce();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
private:
	FVector CalculateSeparationForce(UBehaviorTreeComponent& OwnerComp) const;
	FVector GetSeparationForceFromNeighbour(AActor* ControlledPawn,AActor* Actor, float WeightPercent) const;
	bool ShouldApplyForceFromEnemy(AActor* ControlledPawn,AActor* Actor) const;
	float GetWeightPercent(UBehaviorTreeComponent& OwnerComp) const;
	//Debug
	void VisualiseSeparationForce(const FVector& PawnLocation, const FVector& SeparationForce) const;
	void VisualiseMoveLocationRadius(const FVector& TargetMoveLocation) const;
	void VisualisePersonalSpace(const FVector& PawnLocation) const;
	void VisualisePersonalSpace(const FVector& PawnLocation, const FVector& PawnForward) const;
private:
	UPROPERTY(EditAnywhere, Category = "Settings")
	float PersonalSpaceRadius = 500.f;
	UPROPERTY(EditAnywhere, Category = "Settings")
	float AcceptanceAngle = 500.f;
	UPROPERTY(EditAnywhere, Category = "Settings")
	float AngleThreshold = 20.f;
	UPROPERTY(EditAnywhere, Category = "Settings")
	float SeparationStrength = 400.f;
	
	UPROPERTY(EditAnywhere, Category = "Weight")
	bool UseWeight = true;
	UPROPERTY(EditAnywhere, Category = "Weight")
	float AcceptanceRadiusForMoveLocation = 350.f;
	UPROPERTY(EditAnywhere, Category = "Weight")
	FBlackboardKeySelector MoveLocation;
	UPROPERTY(EditAnywhere, Category = "Gizmos")
	FDebugGizmos Gizmos;
};
