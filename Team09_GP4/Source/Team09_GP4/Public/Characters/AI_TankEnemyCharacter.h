// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/EnemyBase.h"
#include "Interfaces/Damageable.h"
#include "AI_TankEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TEAM09_GP4_API AAI_TankEnemyCharacter : public AEnemyBase
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	AAI_TankEnemyCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UBehaviorTree* GetBehaviorTree() const;


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* Tree;
	
};
