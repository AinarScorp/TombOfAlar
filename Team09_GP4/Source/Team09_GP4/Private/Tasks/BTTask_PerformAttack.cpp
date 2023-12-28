// Fill out your copyright notice in the Description page of Project Settings.


#include "Tasks/BTTask_PerformAttack.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interfaces/Enemy.h"



EBTNodeResult::Type UBTTask_PerformAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!OwnerComp.GetAIOwner()->GetPawn()->Implements<UEnemy>()) return EBTNodeResult::Failed;
	IEnemy::Execute_PerformAttack(OwnerComp.GetAIOwner()->GetPawn());
	SetBlackboardKeyToTrue(OwnerComp);
	return EBTNodeResult::InProgress;
}

