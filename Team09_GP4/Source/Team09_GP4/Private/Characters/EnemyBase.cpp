// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EnemyBase.h"

#include "ActorClasses/CorpseActor.h"
#include "Components/CapsuleComponent.h"
#include "Controllers/AIControllerBase.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/EnemyHordeSubsystem.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	GetMesh()->SetCollisionObjectType(ECC_GameTraceChannel5);
	GetMesh()->SetCollisionResponseToChannel(ECC_GameTraceChannel5, ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_GameTraceChannel4, ECR_Block);
	GetCapsuleComponent()->SetCollisionObjectType(ECC_GameTraceChannel5);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel5, ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel4, ECR_Block);
	
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	OnPlayerHit.AddDynamic(this, &ThisClass::DamagePlayer);
}

void AEnemyBase::Destroyed()
{
	Super::Destroyed();
}

void AEnemyBase::SpawnOnDeathObjects()
{
	for (auto& Pair : OnDeathSpawnObject)
	{
		if (!Pair.Key)
			return;
		int rand = FMath::Rand() % 100;
		if (rand < Pair.Value) {
			GetWorld()->SpawnActor<AActor>(Pair.Key, GetActorTransform());
		}
	}
}




// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (AIControllerBase)
	{
		AIControllerClass = AIControllerBase;
	}
}

void AEnemyBase::TakeDamage_Implementation(float Damage, FVector HitPoint)
{
	//IDamageable::TakeDamage_Implementation(damage, HitPoint);
	CurrentHealth-= Damage;
	if (CurrentHealth<= 0)
	{
		ExecuteDeath();
	}
}

bool AEnemyBase::PerformAttack_Implementation()
{
	if (AttackMontage)
	{
		PlayAnimMontage(AttackMontage);
	}
	return true;
}

bool AEnemyBase::AnimationHasFinished_Implementation()
{
	OnAttackAnimationFinished.Broadcast();
	return true;
}

bool AEnemyBase::ToggleAttackExecution_Implementation(const bool TurnOn)
{
	if (TurnOn)
	{
		StartExecutingAttack();
	}
	else
	{
		FinishExecutingAttack();
	}
	return TurnOn;
}
FVector AEnemyBase::GetWeaponCenterLocation() const
{
	return GetMesh()->GetSocketLocation(WeaponSocketCenter);
}

void AEnemyBase::StartExecutingAttack()
{
	AttackTraceInfo.AttackExecutionPositionLastFrame = GetWeaponCenterLocation();
	AttackExecutionIgnoreActors.Reset();
	GetWorldTimerManager().SetTimer(AttackExecutionTimer,this,&AEnemyBase::ExecuteAttack, UGameplayStatics::GetWorldDeltaSeconds(this), true);
}

void AEnemyBase::FinishExecutingAttack()
{
	GetWorldTimerManager().ClearTimer(AttackExecutionTimer);
}

void AEnemyBase::ExecuteAttack()
{
	TArray<FHitResult> HitResults;
	UKismetSystemLibrary::SphereTraceMulti(this, AttackTraceInfo.AttackExecutionPositionLastFrame, GetWeaponCenterLocation(),
		AttackTraceInfo.AttackTraceRadius,AttackTraceInfo.PlayerChannel,false,AttackExecutionIgnoreActors,AttackTraceInfo.DrawDebugType,HitResults,true,
		AttackTraceInfo.TraceColor,AttackTraceInfo.TraceHitColor,AttackTraceInfo.DrawTime);
	for (FHitResult HitResult : HitResults)
	{
		AttackExecutionIgnoreActors.Add(HitResult.GetActor());
		if (HitResult.GetActor() ==  UGameplayStatics::GetPlayerCharacter(this,0))
		{
			OnPlayerHit.Broadcast(HitResult.GetActor(), HitResult.ImpactPoint);
			FinishExecutingAttack();
			break;
		}
	}
	AttackTraceInfo.AttackExecutionPositionLastFrame = GetWeaponCenterLocation();
}


bool AEnemyBase::ReplaceWithCorpse_Implementation()
{
	ACorpseActor* CorpseActor = GetWorld()->SpawnActor<ACorpseActor>(CorpseActorClass, GetMesh()->GetComponentTransform());
	CorpseActor->SetCorpse(GetMesh()->GetSkeletalMeshAsset(),DeathAnimationPose);
	this->Destroy();
	return true;
}

bool AEnemyBase::ExecuteDeath_Implementation(const bool bKilledByPlayer)
{
	//Remove from Enemy subsystem
	if (AddToSubsystem)
	{
		UEnemyHordeSubsystem* EnemySubsystem = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UEnemyHordeSubsystem>();
		EnemySubsystem->ListOfEnemies.Remove(this);
	}
	//Stop Attack Timer
	FinishExecutingAttack();
	
	DetachFromControllerPendingDestroy();
	//Turn off collision
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PlayAnimMontage(DeathMontage);

	OnDeathExecuted.Broadcast(this,bKilledByPlayer);
	return bKilledByPlayer;
}


