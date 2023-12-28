// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Resettable.h"
//#include "Helpers/SpawnerSettings.h"
#include "EnemySpawner.generated.h"

#pragma region Enums

class AEnemyBase;

UENUM(BlueprintType)
enum class EShowIndex : uint8
{
	ESI_One,
	ESI_Two,
	ESI_Three,
	ESI_Four,
	ESI_Five
};

UENUM(BlueprintType)
enum class ESpawnCount : uint8
{
	ESC_SingleSpawn UMETA(DisplayName = "SingleSpawn"),
	ESC_MulitSpawnSameType UMETA(DisplayName = "MulitSpawnSameType"),
	ESC_MulitSpawnDifferentType UMETA(DisplayName = "MulitSpawnDifferentType"),
};
UENUM(BlueprintType)
enum class ESpawnType : uint8
{
	EST_SpawnAllAtOnce UMETA(DisplayName = "Spawn All At Once"),
	EST_SpawnOneByOne UMETA(DisplayName = "Spawn One By One"),
	EST_SpawnInChunks UMETA(DisplayName = "Spawn In Chunks"),
};

UENUM(BlueprintType)
enum class ESpawnControls : uint8
{
	ESC_SpawnManually UMETA(DisplayName = "Spawn Manually"),
	ESC_UseSpawnRate UMETA(DisplayName = "Use Spawn Rate")
};

#pragma endregion
#pragma region structs
USTRUCT(BlueprintType)
struct FEnemySpawnInfo
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AEnemyBase> EnemyClass;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (EditCondition = "!HideCountOfEnemies",EditConditionHides))
	int CountOfEnemies = 3;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (EditCondition = "!HideDistanceBetweenSpawns",EditConditionHides))
	FVector DistanceBetweenSpawns{100,0,0};
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (EditCondition = "!HideRelativeSpawnLocation",EditConditionHides))
	FVector RelativeSpawnLocation = FVector::ZeroVector;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FColor GizmoColor = FColor::Red;
	
	//TODO Hide from editor
	UPROPERTY()
	bool HideCountOfEnemies = false;
	UPROPERTY()
	bool HideDistanceBetweenSpawns = false;
	UPROPERTY()
	bool HideRelativeSpawnLocation = false;
	
	UPROPERTY()
	int CurrentIndexToSpawn = 0;
};
#pragma region Chunks
USTRUCT(BlueprintType)
struct FChunk
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector DistanceBetweenSpawns{100,100,0};
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector RelativeSpawnLocation = FVector::ZeroVector;
};
USTRUCT(BlueprintType)
struct FChunkSameType: public FChunk
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FEnemySpawnInfo SpawnInfo;

	
};
USTRUCT(BlueprintType)
struct FChunkMultiType: public FChunk
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<FEnemySpawnInfo>SpawnInfoArray;


};
#pragma endregion 
USTRUCT(BlueprintType)
struct FSpawnerSettings
{
	GENERATED_BODY()
	//Displays different things in the editor
	UPROPERTY(BlueprintReadOnly)
	EShowIndex ShowIndex = EShowIndex::ESI_One;
	//Manual or Timer
	UPROPERTY(EditAnywhere,BlueprintReadOnly) 
	ESpawnControls SpawnControls = ESpawnControls::ESC_SpawnManually;
	//Single, MultiType, SameType
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	ESpawnCount SpawnCount{ESpawnCount::ESC_SingleSpawn};
	//Select SpawnType
	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta = (EditCondition = "ShowIndex != EShowIndex::ESI_One",EditConditionHides))
	ESpawnType SpawnType{ESpawnType::EST_SpawnAllAtOnce};
	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta = (EditCondition = "SpawnCount != ESpawnCount::ESC_SingleSpawn && SpawnType != ESpawnType::EST_SpawnAllAtOnce",EditConditionHides))
	float SpawnInterval = 4.f;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	bool SpawnOnStart = false;
    UPROPERTY(EditAnywhere)
	bool ShowGizmos = false;
    UPROPERTY(EditAnywhere)
	float GizmosRadius = 25;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "ShowGizmos &&(ShowIndex == EShowIndex::ESI_Three || ShowIndex == EShowIndex::ESI_Five)",EditConditionHides))
	int ChunkIndexToVisualize = 0;
	

	//Spawn Single Or Same types
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (EditCondition = "ShowIndex == EShowIndex::ESI_Four|| ShowIndex == EShowIndex::ESI_One",EditConditionHides))
	FEnemySpawnInfo SpawnInfo;
	//Different + At once
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (EditCondition = "ShowIndex == EShowIndex::ESI_Two",EditConditionHides))
	TArray<FEnemySpawnInfo> SpawnInfoArray;
	
	//Chunks
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (EditCondition = "ShowIndex == EShowIndex::ESI_Three",EditConditionHides), DisplayName ="ChunkMulti")
	TArray<FChunkMultiType> ChunksMultiType;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (EditCondition = "ShowIndex == EShowIndex::ESI_Five",EditConditionHides), DisplayName ="ChunkSame")
	TArray<FChunkSameType> ChunksSameType;

	UPROPERTY()
	int CurrentChunkToSpawn = 0;
	
	//Function Update Settings
	void UpdateDisplay();
	void HideSomeInfo();
};
#pragma endregion

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpawnerExecutedSignature,AEnemyBase*,SpawnedEnemies);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnSpawnerExhaustedSignature, AEnemySpawner* /*Spawner*/);



UCLASS()
class TEAM09_GP4_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemySpawner();

public:
	UPROPERTY(VisibleAnywhere)
	bool IsExhausted = false;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void TriggerSpawner();
	UFUNCTION(BlueprintCallable)
	void ResetSpawner();
	UFUNCTION()
	void VisualizeSpawner();
	UFUNCTION(BlueprintCallable, Category = "UseWithCaution")
	void GetClassesWithLocations(TArray<FEnemySpawnInfo>& SpawnInfos, TArray<FVector>& Locations, bool IsVisual = false);

	void ResetSpawnedEnemies();
	bool IsSpawnOnStart() const {return SpawnerSettings.SpawnOnStart;}
private:
	
	UFUNCTION()
	void OneEnemy(TArray<FEnemySpawnInfo>& SpawnInfos, TArray<FVector>& Locations);
	UFUNCTION()
	void DifferentEnemiesAtOnce(TArray<FEnemySpawnInfo>& SpawnInfos, TArray<FVector>& Locations);
	UFUNCTION()
	void DifferentEnemiesOneByOne(TArray<FEnemySpawnInfo>& SpawnInfos, TArray<FVector>& Locations, bool IsVisual);
	UFUNCTION()
	void MultiChunk(TArray<FEnemySpawnInfo>& SpawnInfos, TArray<FVector>& Locations, bool IsVisual);
	UFUNCTION()
	void SameChunk(TArray<FEnemySpawnInfo>& SpawnInfos, TArray<FVector>& Locations, bool IsVisual);
	UFUNCTION()
	void SameEnemiesAtOnce(TArray<FEnemySpawnInfo>& SpawnInfos, TArray<FVector>& Locations);
	UFUNCTION()
	void SameEnemiesOneByOne(TArray<FEnemySpawnInfo>& SpawnInfos, TArray<FVector>& Locations, bool IsVisual);
	UFUNCTION()
	AEnemyBase* SpawnEnemy(const FEnemySpawnInfo& SpawnInfo, FVector Location);
	UFUNCTION()
	void ExecuteSpawn();
	UFUNCTION()
	void RemoveEnemyFromList(AEnemyBase* ThisEnemy, bool KilledByPlayer);
	
public:
	UPROPERTY(BlueprintAssignable,BlueprintCallable)
	FOnSpawnerExecutedSignature OnSpawnerExecuted;
	FOnSpawnerExhaustedSignature OnSpawnerExhausted;
private:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category ="EnemySpawner", meta =(AllowPrivateAccess = "true"))
	FSpawnerSettings SpawnerSettings;
	FTimerHandle SpawnTimer;
	UPROPERTY()
	TArray<AEnemyBase*> SpawnedEnemies;

	void AddOneEnemyFromSpawnInfo(FEnemySpawnInfo& SpawnInfo,TArray<FEnemySpawnInfo>& SpawnInfos, TArray<FVector>& Locations, bool IsVisual);
	void GetAllLocationsFromSpawnInfo(const FEnemySpawnInfo& SpawnInfo, TArray<FEnemySpawnInfo>& SpawnInfos, TArray<FVector>& Locations);
};
