// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/EnemyBase.h"
#include "AI_Ambusher.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;
class USphereComponent;

USTRUCT(BlueprintType)
struct FDisguiseMesh
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UStaticMesh* Mesh;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UMaterialInterface* Material;
};

USTRUCT(BlueprintType)
struct FChainFXNames
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FName ChainEndLocationName = "EndLocation";
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FName ChainStartLocationName = "StartLocation";
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FName ChainSocketName = "ChainRayMiddle";
	
	
};
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerDetected, AActor*, Player);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHitPlayer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartedSlowingPlayer);

UCLASS(Abstract)
class TEAM09_GP4_API AAI_Ambusher : public AEnemyBase
{
	GENERATED_BODY()
public:
	AAI_Ambusher();
public:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent)
	void ToggleJump(bool Disappear);
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void StartSlowingPlayer();
	
	virtual bool ExecuteDeath_Implementation(bool KilledByPlayer) override;
	
private:
	UFUNCTION()
	void ChainFXTick();
	void Disguise() const;
	UFUNCTION()
	void UnDisguise(AActor* Player);
public:
	UPROPERTY(BlueprintCallable,BlueprintAssignable)
	FOnPlayerDetected OnPlayerDetected;
	UPROPERTY(BlueprintCallable,BlueprintAssignable)
	FOnHitPlayer OnHitPlayer;
	UPROPERTY(BlueprintAssignable)
	FOnStartedSlowingPlayer OnStartedSlowingPlayer;
private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* DisguiseMesh;
	UPROPERTY(EditAnywhere)
	USphereComponent* SphereComponent;

	UPROPERTY(EditDefaultsOnly, Category = "EnemyBase|Ambusher")
	FDisguiseMesh MeshToDisguise;
	UPROPERTY(EditDefaultsOnly, Category = "EnemyBase|Ambusher|ChainFX")
	FChainFXNames ChainFXNames;
	UPROPERTY(EditDefaultsOnly, Category = "EnemyBase|Ambusher|ChainFX")
	UNiagaraSystem* ChainFX;
	FTimerHandle ChainFXTickTimer;
	UPROPERTY()
	UNiagaraComponent* ChainFXComponent;
	
};
