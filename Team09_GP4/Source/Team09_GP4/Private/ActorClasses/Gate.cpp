// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorClasses/Gate.h"

#include "ActorClasses/EnemySpawner.h"
#include "Characters/EnemyBase.h"

// Sets default values
AGate::AGate()
{
	PrimaryActorTick.bCanEverTick = true;
	EnemyCount = 0;
}

void AGate::BeginPlay()
{
	Super::BeginPlay();
	for (auto &EnemySpawner : SpawnersToWatch)
	{
		if (!EnemySpawner || EnemySpawner->IsSpawnOnStart())
		{
			continue;
		}
		IsSpawnerActive.Add(EnemySpawner,true);
		EnemySpawner->OnSpawnerExecuted.AddDynamic(this, &AGate::AddSpawnedEnemies);
		EnemySpawner->OnSpawnerExhausted.AddUObject(this, &AGate::SetObservingSpawnerToFalse);
	}
}

void AGate::ResetGate()
{
	EnemyCount = 0;
	
}

void AGate::ResetUponPlayerDeath_Implementation()
{
	ResetGate();
}

AActor* AGate::GetActor_Implementation()
{
	return this;
}

void AGate::LockReset_Implementation(bool DeactivateReset)
{
}

void AGate::AddSpawnedEnemies(AEnemyBase* SpawnedEnemy)
{
	if (!SpawnedEnemy)
	{
		return;
	}
	EnemyCount++;
	SpawnedEnemy->OnDeathExecuted.AddDynamic(this, &AGate::CheckIfGateShouldOpen);
}

void AGate::CheckIfGateShouldOpen(AEnemyBase* Enemy, bool KilledByPlayer)
{
	Enemy->OnDeathExecuted.RemoveDynamic(this, &AGate::CheckIfGateShouldOpen);
	if (!KilledByPlayer)
	{
		return;
	}
	EnemyCount--;
	CheckOpenCondition();
}

void AGate::SetObservingSpawnerToFalse(AEnemySpawner* Spawner)
{
	IsSpawnerActive[Spawner] = false;
	CheckOpenCondition();
}

void AGate::CheckOpenCondition()
{
	for (auto &EnemySpawner : IsSpawnerActive)
	{
		if (EnemySpawner.Value == true)
		{
			return;
		}
	}
	if (EnemyCount == 0)
	{
		OnAllEnemiesKilled();
	}
}

void AGate::OnAllEnemiesKilled_Implementation()
{
}


