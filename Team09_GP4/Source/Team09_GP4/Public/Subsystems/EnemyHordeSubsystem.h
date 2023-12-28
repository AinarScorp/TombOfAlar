// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EnemyHordeSubsystem.generated.h"

class AEnemyBase;
/**
 * 
 */
UCLASS()
class TEAM09_GP4_API UEnemyHordeSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "HordeEnemies")
	TArray<AActor*> ListOfEnemies;
	UPROPERTY(BlueprintReadWrite, Category = "HordeEnemies")
	TArray<AEnemyBase*> ListOfRats;
	UPROPERTY(BlueprintReadWrite, Category = "SkeletonArchers")
	TArray<AEnemyBase*> ListOfArchers;
	UPROPERTY(BlueprintReadWrite, Category = "TankEnemies")
	TArray<AEnemyBase*> ListOfTankEnemies;
};
