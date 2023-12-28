// Fill out your copyright notice in the Description page of Project Settings.


#include "Tasks/BTTask_AnimationBasedTask.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_AnimationBasedTask::UBTTask_AnimationBasedTask()
{
	bNotifyTick = true;
	AnimationIsPlayingBool.AddBoolFilter(this,GET_MEMBER_NAME_CHECKED(UBTTask_AnimationBasedTask, AnimationIsPlayingBool));
}

void UBTTask_AnimationBasedTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (!OwnerComp.GetBlackboardComponent()->GetValueAsBool(AnimationIsPlayingBool.SelectedKeyName))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

void UBTTask_AnimationBasedTask::SetBlackboardKeyToTrue(UBehaviorTreeComponent& OwnerComp) const
{
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AnimationIsPlayingBool.SelectedKeyName, true);

}

