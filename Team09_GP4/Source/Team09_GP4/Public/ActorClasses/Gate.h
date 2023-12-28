// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Resettable.h"
#include "Gate.generated.h"

class AEnemyBase;
class AEnemySpawner;

UCLASS()
class TEAM09_GP4_API AGate : public AActor, public IResettable
{
	GENERATED_BODY()
	
public:	
	AGate();
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintNativeEvent)
	void OnAllEnemiesKilled();
	UFUNCTION(BlueprintCallable)
	void ResetGate();
	virtual void ResetUponPlayerDeath_Implementation() override;
	virtual AActor* GetActor_Implementation() override;
	virtual void LockReset_Implementation(bool DeactivateReset) override;
private:
	
	UFUNCTION()
	void AddSpawnedEnemies(AEnemyBase* SpawnedEnemy);
	UFUNCTION()
	void CheckIfGateShouldOpen(AEnemyBase* Enemy, bool KilledByPlayer);
	void SetObservingSpawnerToFalse(AEnemySpawner* Spawner);
	void CheckOpenCondition();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<AEnemySpawner*> SpawnersToWatch;
	UPROPERTY(VisibleAnywhere)
	TMap<AEnemySpawner*,bool> IsSpawnerActive;
	int EnemyCount;

};
