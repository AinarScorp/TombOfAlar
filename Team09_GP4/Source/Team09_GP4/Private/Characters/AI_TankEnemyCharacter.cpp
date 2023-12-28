// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI_TankEnemyCharacter.h"

AAI_TankEnemyCharacter::AAI_TankEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAI_TankEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UBehaviorTree* AAI_TankEnemyCharacter::GetBehaviorTree() const
{
	return Tree;
}