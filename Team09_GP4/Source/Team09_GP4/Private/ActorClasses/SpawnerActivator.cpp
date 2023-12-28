// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorClasses/SpawnerActivator.h"

#include "ActorClasses/EnemySpawner.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASpawnerActivator::ASpawnerActivator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollsion");
	BoxCollision->SetCollisionProfileName(TEXT("IgnoreAllButOverlapPlayer"));
}



void ASpawnerActivator::BeginPlay()
{
	Super::BeginPlay();
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ASpawnerActivator::TriggerSpawners);
	for (auto Spawner : EnemySpawners)
	{
		if (Spawner)
		{
			Spawner->OnSpawnerExhausted.AddUObject(this,&ASpawnerActivator::TurnOffCollsions);
		}
	}
}


void ASpawnerActivator::TriggerSpawners(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,const FHitResult& SweepResult)
{
	if (UGameplayStatics::GetPlayerCharacter(GetWorld(),0) != OtherActor)
	{
		return;
	}
	for (auto Spawner : EnemySpawners)
	{
		if (Spawner)
		{
			Spawner->TriggerSpawner();
		}
	}
	

}

void ASpawnerActivator::TurnOffCollsions(AEnemySpawner* Spawner)
{
	for (const auto& EnemySpawner : EnemySpawners)
	{
		if (EnemySpawner->IsExhausted)
		{
			return;
		}
	}
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASpawnerActivator::ResetSpawners()
{
	for (auto Spawner : EnemySpawners)
	{
		if (Spawner)
		{
			Spawner->ResetSpawner();
		}
	}
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

}

void ASpawnerActivator::ResetUponPlayerDeath_Implementation()
{
	if (ResetIsDeactivated)
	{
		return;
	}
	ResetSpawners();
	
}

AActor* ASpawnerActivator::GetActor_Implementation()
{
	return this;
}

void ASpawnerActivator::LockReset_Implementation(bool DeactivateReset)
{
	ResetIsDeactivated = DeactivateReset;
}
