#pragma once
#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Interfaces/Damageable.h"
#include "AI_CoverCharacter.generated.h"

UCLASS()
class TEAM09_GP4_API AAI_CoverCharacter : public AEnemyBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAI_CoverCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UBehaviorTree* GetBehaviorTree() const;

	UFUNCTION(BlueprintImplementableEvent)
		void FireWeapon();


	UFUNCTION(Blueprintable, BlueprintCallable)
	FVector GetTargetLocationFromBlackboard();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		UBehaviorTree* Tree = nullptr;
	
};
