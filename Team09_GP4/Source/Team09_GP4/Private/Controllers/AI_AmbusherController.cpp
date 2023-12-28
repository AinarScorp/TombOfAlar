// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/AI_AmbusherController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/AI_Ambusher.h"
#include "Kismet/GameplayStatics.h"

void AAI_AmbusherController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	PossessedAmbusher = Cast<AAI_Ambusher>(InPawn);
	if (!PossessedAmbusher) return;

	PossessedAmbusher->OnPlayerDetected.AddDynamic(this, &AAI_AmbusherController::StartBehaviourTreeUponNoticingPlayer);
	PossessedAmbusher->OnHitPlayer.AddDynamic(this, &AAI_AmbusherController::SetTrueToHasHitPlayerKey);
}

void AAI_AmbusherController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AAI_AmbusherController::StartBehaviourTreeUponNoticingPlayer(AActor* Player)
{
	RunBehaviorTree(PossessedAmbusher->BehaviorTree);
	PossessedAmbusher->OnAttackAnimationFinished.AddDynamic(this,&AAI_AmbusherController::SetFalseToAnimationIsPlayingKey);
	Blackboard.Get()->SetValueAsObject(GetEnemyBlackboardKey(EEnemyBlackboardKeys::EEBK_TargetToMove),UGameplayStatics::GetPlayerCharacter(this,0));
	PossessedAmbusher->OnPlayerDetected.RemoveDynamic(this, &AAI_AmbusherController::StartBehaviourTreeUponNoticingPlayer);

	
}

void AAI_AmbusherController::SetTrueToHasHitPlayerKey()
{
	Blackboard.Get()->SetValueAsBool(GetEnemyBlackboardKey(EEnemyBlackboardKeys::EEBK_HasHitPlayer),true);
	PossessedAmbusher->OnHitPlayer.RemoveDynamic(this, &AAI_AmbusherController::SetTrueToHasHitPlayerKey);

}
