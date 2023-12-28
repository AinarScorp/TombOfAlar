// Fill out your copyright notice in the Description page of Project Settings.
#include "Tasks/BTTask_FireShot.h"
#include "AIController.h"
#include "Characters/AI_CoverCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


EBTNodeResult::Type UBTTask_FireShot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAI_CoverCharacter* Character = Cast<AAI_CoverCharacter>(OwnerComp.GetAIOwner()->GetCharacter());
	if(Character)
	{
		Character->FireWeapon();
	}
	
	return EBTNodeResult::Succeeded;
}
