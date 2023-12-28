#pragma once
#include "CoreMinimal.h"
#include "AIControllerBase.h"
#include "AI_CoverController.generated.h"

UCLASS()
class TEAM09_GP4_API AAI_CoverController : public AAIControllerBase
{
	GENERATED_BODY()

public:
	AAI_CoverController(FObjectInitializer const& ObjectInitializer) {}

protected:
	virtual void OnPossess(APawn* InPawn) override;

};
