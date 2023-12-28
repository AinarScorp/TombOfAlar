#include "Characters/AI_CoverCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Controllers/AI_CoverController.h"

// Sets default values
AAI_CoverCharacter::AAI_CoverCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


FVector AAI_CoverCharacter::GetTargetLocationFromBlackboard()
{
	AAI_CoverController* temp = GetController<AAI_CoverController>();
	FVector location = temp->GetBlackboardComponent()->GetValueAsVector("TargetLocation");
	return temp->GetBlackboardComponent()->GetValueAsVector("TargetLocation");
}

// Called when the game starts or when spawned
void AAI_CoverCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAI_CoverCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UBehaviorTree* AAI_CoverCharacter::GetBehaviorTree() const {
	return Tree;
}
