#include "Controllers/AI_TankEnemyController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/AI_TankEnemyCharacter.h"

void AAI_TankEnemyController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);

	if (const AAI_TankEnemyCharacter* const TankEnemyCharacter = Cast<AAI_TankEnemyCharacter>(InPawn)) {
		if (UBehaviorTree* const BehaviorTree = TankEnemyCharacter->GetBehaviorTree()) {
			UBlackboardComponent* BlackboardComponent;
			UseBlackboard(BehaviorTree->BlackboardAsset, BlackboardComponent);
			Blackboard = BlackboardComponent;
			RunBehaviorTree(BehaviorTree);
			
			BlackboardComponent->SetValueAsBool(CanJumpKeyName, true);
			BlackboardComponent->SetValueAsFloat(JumpCooldownKeyName, JumpCooldown);
		}
	}
}


