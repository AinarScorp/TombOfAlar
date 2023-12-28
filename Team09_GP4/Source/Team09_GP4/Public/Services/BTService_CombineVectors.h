// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CombineVectors.generated.h"

USTRUCT()
struct FVectorInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Setting")
	bool Add_X = true;
	UPROPERTY(EditAnywhere, Category = "Setting")
	bool Add_Y = true;
	UPROPERTY(EditAnywhere, Category = "Setting")
	bool Add_Z = false;
	UPROPERTY(EditAnywhere, Category = "Setting")
	bool AddDirectionOnly = true;

	UPROPERTY(EditAnywhere, Category = "Setting")
	FBlackboardKeySelector BlackboardKey;
	
};
/**
 * 
 */
UCLASS()
class TEAM09_GP4_API UBTService_CombineVectors : public UBTService
{
	GENERATED_BODY()
public:
	UBTService_CombineVectors();
	
public:
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
private:
	FVector CombineVectors(UBehaviorTreeComponent& OwnerComp);
	static FVector GetVectorFromBlackboardKey(UBehaviorTreeComponent& OwnerComp, FBlackboardKeySelector& Key);
	void VisualiseCombinedVector(const FVector& PawnLocation, const FVector& CombinedVector) const;

public:
	UPROPERTY(EditAnywhere, Category = "Setting")
	TArray<FVectorInfo> VectorsToCombine;
	UPROPERTY(EditAnywhere, Category = "Setting")
	bool AddPawnLocation = true;
	UPROPERTY(EditAnywhere, Category = "Setting")
	FBlackboardKeySelector KeyToAssignInto;
	
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool DrawCombinedVector = true;
	
	
};
