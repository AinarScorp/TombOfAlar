// Fill out your copyright notice in the Description page of Project Settings.


#include "Tasks/BTTask_ToggleAmbusherJump.h"

#include "AIController.h"
#include "Characters/AI_Ambusher.h"


EBTNodeResult::Type UBTTask_ToggleAmbusherJump::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAI_Ambusher* Ambusher = Cast<AAI_Ambusher>(OwnerComp.GetAIOwner()->GetPawn());
	if (!Ambusher) return EBTNodeResult::Failed;
	SetBlackboardKeyToTrue(OwnerComp);
	Ambusher->ToggleJump(Disappear);
	return EBTNodeResult::InProgress;
}

