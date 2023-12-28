// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorClasses/EnemySpawner.h"

#include "Characters/EnemyBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Subsystems/EnemyHordeSubsystem.h"

#pragma region  Struct Functions

void FSpawnerSettings::UpdateDisplay()
{
	switch (SpawnCount) {
	case ESpawnCount::ESC_SingleSpawn:
		ShowIndex = EShowIndex::ESI_One;
		break;
	case ESpawnCount::ESC_MulitSpawnSameType:
		ShowIndex = SpawnType == ESpawnType::EST_SpawnInChunks ? EShowIndex::ESI_Five : EShowIndex::ESI_Four;
		break;
	case ESpawnCount::ESC_MulitSpawnDifferentType:
		ShowIndex = SpawnType == ESpawnType::EST_SpawnInChunks ? EShowIndex::ESI_Three : EShowIndex::ESI_Two;
		break;
	}
}

void FSpawnerSettings::HideSomeInfo()
{
	SpawnInfo.HideCountOfEnemies = SpawnCount == ESpawnCount::ESC_SingleSpawn;
	SpawnInfo.HideDistanceBetweenSpawns = SpawnCount == ESpawnCount::ESC_SingleSpawn;
	SpawnInfo.HideRelativeSpawnLocation = SpawnCount == ESpawnCount::ESC_SingleSpawn;
	
	if (SpawnType == ESpawnType::EST_SpawnAllAtOnce)
	{
		return;
	}
	
	if (SpawnCount == ESpawnCount::ESC_MulitSpawnDifferentType)
	{
		if (SpawnType == ESpawnType::EST_SpawnOneByOne)
		{
			for (auto& EnemySpawnInfo : SpawnInfoArray)
			{
				EnemySpawnInfo.HideDistanceBetweenSpawns =true;
			}
			return;
		}
		
		for (auto& Chunk : ChunksMultiType)
		{
			for (auto& EnemySpawnInfo : Chunk.SpawnInfoArray)
			{
				EnemySpawnInfo.HideDistanceBetweenSpawns = true; 
				EnemySpawnInfo.HideRelativeSpawnLocation = true; 

			}
		}
	}
	else if (SpawnCount == ESpawnCount::ESC_MulitSpawnSameType)
	{
		if (SpawnType == ESpawnType::EST_SpawnOneByOne)
		{
			SpawnInfo.HideDistanceBetweenSpawns = true;
		}
		for (auto& Chunk : ChunksSameType)
		{
			Chunk.SpawnInfo.HideDistanceBetweenSpawns = true;
			Chunk.SpawnInfo.HideRelativeSpawnLocation = SpawnType == ESpawnType::EST_SpawnInChunks;;

		}
	}

	
}
#pragma endregion 

AEnemySpawner::AEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AEnemySpawner::TriggerSpawner()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(SpawnTimer) || IsExhausted)  return;

	if (SpawnerSettings.SpawnControls == ESpawnControls::ESC_SpawnManually)
	{
		ExecuteSpawn();
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &AEnemySpawner::ExecuteSpawn, SpawnerSettings.SpawnInterval, true,0.01f);
	}
}

void AEnemySpawner::ResetSpawner()
{
	SpawnerSettings.SpawnInfo.CurrentIndexToSpawn = 0;
	SpawnerSettings.CurrentChunkToSpawn = 0;
	for (auto& SpawnInfo : SpawnerSettings.SpawnInfoArray)
	{
		SpawnInfo.CurrentIndexToSpawn = 0;
	}
	GetWorld()->GetTimerManager().ClearTimer(SpawnTimer);
	if (SpawnerSettings.SpawnOnStart)
	{
		TriggerSpawner();
	}
	ResetSpawnedEnemies();
	IsExhausted = false;
}

void AEnemySpawner::VisualizeSpawner()
{
	if (!SpawnerSettings.ShowGizmos) return;

	UKismetSystemLibrary::FlushPersistentDebugLines(GetWorld());
	
	TArray<FEnemySpawnInfo> SpawnInfos;
	TArray<FVector> Locations;
	GetClassesWithLocations(SpawnInfos, Locations,true);
	for (int i = 0; i < SpawnInfos.Num(); ++i)
	{
		DrawDebugSphere(GetWorld(),Locations[i],SpawnerSettings.GizmosRadius,12, SpawnInfos[i].GizmoColor,true, 1,0,1);
	}
}



void AEnemySpawner::GetClassesWithLocations(TArray<FEnemySpawnInfo>& SpawnInfos, TArray<FVector>& Locations, bool IsVisual)
{
	switch (SpawnerSettings.ShowIndex)
	{
	case EShowIndex::ESI_One:
		OneEnemy(SpawnInfos,Locations);
		break;
	case EShowIndex::ESI_Two:
		if (SpawnerSettings.SpawnType == ESpawnType::EST_SpawnAllAtOnce)
		{
			DifferentEnemiesAtOnce(SpawnInfos, Locations);
		}
		else if (SpawnerSettings.SpawnType == ESpawnType::EST_SpawnOneByOne)
		{
			DifferentEnemiesOneByOne(SpawnInfos,Locations,IsVisual);
		}
		break;
	case EShowIndex::ESI_Three:
		MultiChunk(SpawnInfos,Locations, IsVisual);
		break;
	case EShowIndex::ESI_Four:
		if (SpawnerSettings.SpawnType == ESpawnType::EST_SpawnAllAtOnce)
		{
			SameEnemiesAtOnce(SpawnInfos,Locations);
		}
		else if (SpawnerSettings.SpawnType == ESpawnType::EST_SpawnOneByOne)
		{
			SameEnemiesOneByOne(SpawnInfos,Locations,IsVisual);
		}
		break;
	case EShowIndex::ESI_Five:
		SameChunk(SpawnInfos,Locations,IsVisual);
		break;
	default: ;
	}
}


void AEnemySpawner::ResetSpawnedEnemies()
{
	TArray<AEnemyBase*> EnemiesToKill = SpawnedEnemies;
	
	for (auto Enemy : EnemiesToKill)
	{
		if (!Enemy)
		{
			continue;
		}
		Enemy->ExecuteDeath(false);
	}
	SpawnedEnemies.Empty();
}


void AEnemySpawner::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SpawnerSettings.UpdateDisplay();
	SpawnerSettings.HideSomeInfo();
	VisualizeSpawner();
}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	if (SpawnerSettings.SpawnOnStart)
	{
		TriggerSpawner();
	}
}

void AEnemySpawner::OneEnemy(TArray<FEnemySpawnInfo>& SpawnInfos, TArray<FVector>& Locations)
{
	FVector Location = GetActorLocation() + SpawnerSettings.SpawnInfo.RelativeSpawnLocation;
	SpawnInfos.Add(SpawnerSettings.SpawnInfo);
	Locations.Add(Location);
	//SpawnEnemy(SpawnerSettings.SpawnInfo,Location);
}

void AEnemySpawner::DifferentEnemiesAtOnce(TArray<FEnemySpawnInfo>& SpawnInfos, TArray<FVector>& Locations)
{
	for (auto& SpawnInfo : SpawnerSettings.SpawnInfoArray)
	{
		GetAllLocationsFromSpawnInfo(SpawnInfo,SpawnInfos,Locations);
	}
}

void AEnemySpawner::DifferentEnemiesOneByOne(TArray<FEnemySpawnInfo>& SpawnInfos, TArray<FVector>& Locations, bool IsVisual)
{
	for (auto& SpawnInfo : SpawnerSettings.SpawnInfoArray)
	{
		if (SpawnInfo.CurrentIndexToSpawn >= SpawnInfo.CountOfEnemies) continue;
		AddOneEnemyFromSpawnInfo(SpawnInfo,SpawnInfos,Locations, IsVisual);
	}
}

void AEnemySpawner::MultiChunk(TArray<FEnemySpawnInfo>& SpawnInfos, TArray<FVector>& Locations, bool IsVisual)
{
	int NumberToCompare = IsVisual? SpawnerSettings.ChunkIndexToVisualize : SpawnerSettings.CurrentChunkToSpawn;
	if (SpawnerSettings.ChunksMultiType.Num() <= NumberToCompare) return;

	FChunkMultiType& Chunk = SpawnerSettings.ChunksMultiType[NumberToCompare];
	int CountTotal = 0;

	for (auto SpawnInfo : Chunk.SpawnInfoArray)
	{
		CountTotal += SpawnInfo.CountOfEnemies;
	}

	int SquaredCount = FMath::CeilToInt(UKismetMathLibrary::Sqrt(CountTotal));
	for (int x = 0; x < SquaredCount; ++x)
	{
		for (int y = 0; y < SquaredCount; ++y)
		{
			FVector GridVector = Chunk.DistanceBetweenSpawns;
			GridVector.X *= x;
			GridVector.Y *= y;

			FVector Location = GetActorLocation() + Chunk.RelativeSpawnLocation + GridVector;
			Locations.Add(Location);
		}
	}
	int EnemiesSpawned = 0;
	for (auto SpawnInfo : Chunk.SpawnInfoArray)
	{
		for (int i = 0; i < SpawnInfo.CountOfEnemies; ++i)
		{
			SpawnInfos.Add(SpawnInfo);
			//SpawnEnemy(SpawnInfo,Locations[EnemiesSpawned]);
			EnemiesSpawned++;
		}
	}
	if (!IsVisual)
	{
		SpawnerSettings.CurrentChunkToSpawn++;
	}
}

void AEnemySpawner::SameChunk(TArray<FEnemySpawnInfo>& SpawnInfos, TArray<FVector>& Locations, bool IsVisual)
{
	int NumberToCompare = IsVisual? SpawnerSettings.ChunkIndexToVisualize : SpawnerSettings.CurrentChunkToSpawn;

	if (SpawnerSettings.ChunksSameType.Num() <= NumberToCompare) return;
	FChunkSameType& Chunk = SpawnerSettings.ChunksSameType[NumberToCompare];
	int CountTotal = Chunk.SpawnInfo.CountOfEnemies;

	int SquaredCount = FMath::CeilToInt(UKismetMathLibrary::Sqrt(CountTotal));
	for (int x = 0; x < SquaredCount; ++x)
	{
		for (int y = 0; y < SquaredCount; ++y)
		{
			FVector GridVector = Chunk.DistanceBetweenSpawns;
			GridVector.X *= x;
			GridVector.Y *= y;

			FVector Location = GetActorLocation() + Chunk.RelativeSpawnLocation + GridVector;
			Locations.Add(Location);
		}
	}
	for (int i = 0; i < CountTotal; ++i)
	{
		SpawnInfos.Add(Chunk.SpawnInfo);
		//SpawnEnemy(Chunk.SpawnInfo,Locations[i]);
	}
	if (!IsVisual)
	{
		SpawnerSettings.CurrentChunkToSpawn++;
	}
}

void AEnemySpawner::SameEnemiesAtOnce(TArray<FEnemySpawnInfo>& SpawnInfos, TArray<FVector>& Locations)
{
	GetAllLocationsFromSpawnInfo(SpawnerSettings.SpawnInfo,SpawnInfos, Locations);
}

void AEnemySpawner::SameEnemiesOneByOne(TArray<FEnemySpawnInfo>& SpawnInfos, TArray<FVector>& Locations, bool IsVisual)
{
	AddOneEnemyFromSpawnInfo(SpawnerSettings.SpawnInfo,SpawnInfos, Locations,IsVisual);
}



void AEnemySpawner::AddOneEnemyFromSpawnInfo(FEnemySpawnInfo& SpawnInfo,TArray<FEnemySpawnInfo>& SpawnInfos, TArray<FVector>& Locations, bool IsVisual)
{
	if (SpawnInfo.CurrentIndexToSpawn >= SpawnInfo.CountOfEnemies) return;
	FVector Location = GetActorLocation() + SpawnInfo.RelativeSpawnLocation;
	SpawnInfos.Add(SpawnInfo);
	Locations.Add(Location);
	//SpawnEnemy(SpawnInfo,Location);
	if (!IsVisual)
	{
		SpawnInfo.CurrentIndexToSpawn++;
	}
}

void AEnemySpawner::GetAllLocationsFromSpawnInfo(const FEnemySpawnInfo& SpawnInfo,TArray<FEnemySpawnInfo>& SpawnInfos, TArray<FVector>& Locations)
{
	for (int i = 0 - (SpawnInfo.CountOfEnemies / 2); i < SpawnInfo.CountOfEnemies - (SpawnInfo.CountOfEnemies / 2); ++i)
	{
		FVector SpawnLocation = GetActorLocation() + SpawnInfo.RelativeSpawnLocation + (i * SpawnInfo.DistanceBetweenSpawns);
		SpawnInfos.Add(SpawnInfo);
		Locations.Add(SpawnLocation);
		//SpawnEnemy(SpawnInfo, SpawnLocation);
	}
}

AEnemyBase* AEnemySpawner::SpawnEnemy(const FEnemySpawnInfo& SpawnInfo, FVector Location)
{
	AEnemyBase* Enemy =GetWorld()->SpawnActor<AEnemyBase>(SpawnInfo.EnemyClass, Location, FRotator::ZeroRotator);
	if (!Enemy)
	{
		return nullptr;
	}
	if (Enemy->ShouldAddToEnemySubsystem())
	{
		UEnemyHordeSubsystem* EnemySubsystem = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UEnemyHordeSubsystem>();
		EnemySubsystem->ListOfEnemies.Add(Enemy);
	}
	SpawnedEnemies.Add(Enemy);
	
	Enemy->OnDeathExecuted.AddDynamic(this, &AEnemySpawner::RemoveEnemyFromList);
	return Enemy;

}

void AEnemySpawner::ExecuteSpawn()
{
	TArray<FEnemySpawnInfo> SpawnInfos;
	TArray<FVector> Locations;

	GetClassesWithLocations(SpawnInfos, Locations,false);
	for (int i = 0; i < SpawnInfos.Num(); ++i)
	{
		OnSpawnerExecuted.Broadcast(SpawnEnemy(SpawnInfos[i],Locations[i]));
	}
	bool OneTimeExecution = SpawnerSettings.SpawnType == ESpawnType::EST_SpawnAllAtOnce || SpawnerSettings.SpawnCount == ESpawnCount::ESC_SingleSpawn;
	bool SpawningInChunks = SpawnerSettings.SpawnType == ESpawnType::EST_SpawnInChunks;
	bool ChunkSameTypeIsExhausted = SpawnerSettings.SpawnCount == ESpawnCount::ESC_MulitSpawnSameType && SpawnerSettings.ChunksSameType.Num() == SpawnerSettings.CurrentChunkToSpawn;
	bool ChunkMultiTypeIsExhausted = SpawnerSettings.SpawnCount == ESpawnCount::ESC_MulitSpawnDifferentType && SpawnerSettings.ChunksMultiType.Num() == SpawnerSettings.CurrentChunkToSpawn;
	bool ChunkIsExhausted = SpawningInChunks && (ChunkMultiTypeIsExhausted|| ChunkSameTypeIsExhausted);
	if (SpawnInfos.Num()<=0||OneTimeExecution||ChunkIsExhausted)
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimer);
		IsExhausted = true;
		OnSpawnerExhausted.Broadcast(this);

		
	}
	
}

void AEnemySpawner::RemoveEnemyFromList(AEnemyBase* ThisEnemy, bool KilledByPlayer)
{
	SpawnedEnemies.Remove(ThisEnemy);
	ThisEnemy->OnDeathExecuted.RemoveDynamic(this, &AEnemySpawner::RemoveEnemyFromList);

}
