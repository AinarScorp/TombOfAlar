// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/AI_RatController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/EnemyBase.h"
#include "Kismet/GameplayStatics.h"

void AAI_RatController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	AEnemyBase* EnemyBase = Cast<AEnemyBase>(InPawn);
	if (!EnemyBase) return;

	
	RunBehaviorTree(EnemyBase->BehaviorTree);
	EnemyBase->OnAttackAnimationFinished.AddDynamic(this,&AAIControllerBase::SetFalseToAnimationIsPlayingKey);
	Blackboard.Get()->SetValueAsObject(GetEnemyBlackboardKey(EEnemyBlackboardKeys::EEBK_TargetToMove),UGameplayStatics::GetPlayerCharacter(this,0));

}
