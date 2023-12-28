#pragma once
#include "CoreMinimal.h"
#include "AIControllerBase.h"
#include "AI_TankEnemyController.generated.h"

UCLASS()
class TEAM09_GP4_API AAI_TankEnemyController : public AAIControllerBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category="JumpCooldown")
	float JumpCooldown = 5.f;

	const FName CanJumpKeyName = "CanJump";
	const FName JumpCooldownKeyName = "JumpCooldown";

public:
	AAI_TankEnemyController(FObjectInitializer const& ObjectInitializer) {}
	
protected:
	virtual void OnPossess(APawn* InPawn) override;
};
