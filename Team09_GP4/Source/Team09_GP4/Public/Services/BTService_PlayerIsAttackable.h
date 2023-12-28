#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_PlayerIsAttackable.generated.h"

UCLASS()
class TEAM09_GP4_API UBTService_PlayerIsAttackable : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	UBTService_PlayerIsAttackable(){}
	
	UPROPERTY(EditAnywhere)
	float MinRangeFromTarget = 0.f;

	UPROPERTY(EditAnywhere)
	float MaxRangeFromTarget = 0.f;

	const FName CanAttackKeyName = "CanAttack";
	const FName PlayerActorKeyName = "PlayerActor";
	const FName PlayerLocationKeyName = "PlayerLocation";
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
