// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/AIControllerBase.h"

#include "BehaviorTree/BlackboardComponent.h"

void AAIControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
}

FName AAIControllerBase::GetEnemyBlackboardKey(const EEnemyBlackboardKeys BlackboardKey)
{
	return *UEnum::GetDisplayValueAsText(BlackboardKey).ToString();
}


void AAIControllerBase::SetFalseToAnimationIsPlayingKey()
{
	Blackboard.Get()->SetValueAsBool(GetEnemyBlackboardKey(EEnemyBlackboardKeys::EEBK_AnimationIsPlaying),false);
}
