#include "Services/BTService_JumpCooldown.h"

#include "BehaviorTree/BlackboardComponent.h"

void UBTService_JumpCooldown::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();

	if(!BlackboardComponent->GetValueAsBool(CanJumpKeyName))
	{
		CooldownTimer += DeltaSeconds;
		if(CooldownTimer > BlackboardComponent->GetValueAsFloat(JumpCooldownKeyName))
		{
			BlackboardComponent->SetValueAsBool(CanJumpKeyName, true);
			CooldownTimer = 0.f;
		}
	}
}
