// Fill out your copyright notice in the Description page of Project Settings.

#include "Controllers/AI_CoverController.h"
#include "Characters/AI_CoverCharacter.h"

void AAI_CoverController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);

	if (AAI_CoverCharacter* const npc = Cast<AAI_CoverCharacter>(InPawn)) {
		if (UBehaviorTree* const tree = npc->GetBehaviorTree()) {
			UBlackboardComponent* b;
			UseBlackboard(tree->BlackboardAsset, b);
			Blackboard = b;
			RunBehaviorTree(tree);
		}
	}
}