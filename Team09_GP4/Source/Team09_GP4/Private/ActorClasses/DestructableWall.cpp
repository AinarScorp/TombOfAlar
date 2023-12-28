// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorClasses/DestructableWall.h"

// Sets default values
ADestructableWall::ADestructableWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ADestructableWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestructableWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

