// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Resettable.h"
#include "SpawnerActivator.generated.h"

class AEnemySpawner;
class UBoxComponent;
class UPrimitiveComponent;
UCLASS()
class TEAM09_GP4_API ASpawnerActivator : public AActor, public IResettable 
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnerActivator();
	
	UFUNCTION(BlueprintCallable)
	void ResetSpawners();
	virtual void ResetUponPlayerDeath_Implementation() override;
	virtual AActor* GetActor_Implementation() override;
	virtual void LockReset_Implementation(bool DeactivateReset) override;
protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollision;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<AEnemySpawner*> EnemySpawners;
	UFUNCTION()
	void TriggerSpawners(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	void TurnOffCollsions(AEnemySpawner* Spawner);

	UPROPERTY(BlueprintReadWrite, meta =(AllowPrivateAccess = "true"))
	bool ResetIsDeactivated = false;

};
