// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Damageable.h"
#include "Interfaces/Enemy.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EnemyBase.generated.h"
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttackIsToggledSignature, bool, AttackOn);

class ACorpseActor;
class AAIControllerBase;
class UBehaviorTree;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDeathExecuted, AEnemyBase*, ThisEnemy, bool, KilledByPlayer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackAnimationFinished);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerHit, AActor*, Player, FVector, HitLocation);

USTRUCT()
struct FAttackTraceInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<ETraceTypeQuery> PlayerChannel = TraceTypeQuery4;
	UPROPERTY(EditDefaultsOnly)
	float AttackTraceRadius = 50.f;

	FVector AttackExecutionPositionLastFrame;

//Debug
	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType = EDrawDebugTrace::Type::None;
	UPROPERTY(EditDefaultsOnly)
	FLinearColor TraceColor = FLinearColor::Red;
	UPROPERTY(EditDefaultsOnly)
	FLinearColor TraceHitColor = FLinearColor::Blue;
	UPROPERTY(EditDefaultsOnly)
	float DrawTime = 3.0f;
};
UCLASS(Abstract)
class TEAM09_GP4_API AEnemyBase : public ACharacter, public IDamageable, public IEnemy
{
	GENERATED_BODY()

public:
	AEnemyBase();

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;
	bool ShouldAddToEnemySubsystem() const { return AddToSubsystem;};

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool ExecuteDeath(bool KilledByPlayer = true);
#pragma region Interfaces
	virtual void TakeDamage_Implementation(float Damage, FVector HitPoint) override;
	virtual bool PerformAttack_Implementation() override;
	virtual bool AnimationHasFinished_Implementation() override;
	virtual bool ToggleAttackExecution_Implementation(bool TurnOn) override;
	virtual bool ReplaceWithCorpse_Implementation() override;
#pragma endregion
protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

	UFUNCTION(BlueprintCallable)
	virtual void SpawnOnDeathObjects();
protected:
	UFUNCTION(BlueprintCallable,BlueprintPure)
	FVector GetWeaponCenterLocation() const;
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void DamagePlayer(AActor* Player, FVector HitLocation);
private:
	void ExecuteAttack();
	void StartExecutingAttack();
	void FinishExecutingAttack();

public:
	UPROPERTY(BlueprintAssignable,BlueprintCallable, Category ="EnemyBase|Animation")
	FOnAttackAnimationFinished OnAttackAnimationFinished;
	UPROPERTY(BlueprintAssignable,BlueprintCallable, Category ="EnemyBase|Attack")
	FOnPlayerHit OnPlayerHit;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnemyBase|Setup|AI")
	UBehaviorTree* BehaviorTree;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnemyBase|Setup|AI")
	TSubclassOf<AAIControllerBase> AIControllerBase;

	
	
	//Move this stuff into a data asset
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnemyBase|OnDeath|Drop Object and Drop Percentage ")
	TMap<TSubclassOf<AActor>, int> OnDeathSpawnObject;
	UPROPERTY(BlueprintAssignable)
	FOnDeathExecuted OnDeathExecuted;
private:
	//Attack
	UPROPERTY(EditDefaultsOnly,Category = "EnemyBase|Attack")
	FName WeaponSocketCenter;
	UPROPERTY(EditDefaultsOnly,Category = "EnemyBase|Attack|Animation")
	UAnimMontage* AttackMontage;

	FTimerHandle AttackExecutionTimer;
	UPROPERTY(EditDefaultsOnly,Category = "EnemyBase|Attack")
	FAttackTraceInfo AttackTraceInfo;
	UPROPERTY()
	TArray<AActor*> AttackExecutionIgnoreActors;


	UPROPERTY(EditDefaultsOnly, Category = "EnemyBase|Death")
	TSubclassOf<ACorpseActor> CorpseActorClass;
	UPROPERTY(EditDefaultsOnly, Category = "EnemyBase|Death|Animation")
	UAnimationAsset* DeathAnimationPose;
	UPROPERTY(EditDefaultsOnly,Category = "EnemyBase|Death|Animation")
	UAnimMontage* DeathMontage;
	UPROPERTY(EditDefaultsOnly)
	bool AddToSubsystem = true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = "EnemyBase|Setup|Health", meta = (AllowPrivateAccess = "true"))
	float MaxHealth;
	UPROPERTY(BlueprintReadWrite,Category = "EnemyBase|Setup|Health", meta = (AllowPrivateAccess = "true"))
	float CurrentHealth;
};
