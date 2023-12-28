// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AI_Ambusher.h"

#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"


AAI_Ambusher::AAI_Ambusher()
{
	DisguiseMesh = CreateDefaultSubobject<UStaticMeshComponent>("DisguiseMesh");
	DisguiseMesh->SetupAttachment(GetRootComponent());
	DisguiseMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere Trap");
	SphereComponent->SetupAttachment(DisguiseMesh);
	SphereComponent->SetSphereRadius(640);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	
}

void AAI_Ambusher::BeginPlay()
{
	Super::BeginPlay();
	Disguise();
	OnPlayerDetected.AddDynamic(this, &ThisClass::UnDisguise);
}

void AAI_Ambusher::StartSlowingPlayer_Implementation()
{
	ChainFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,ChainFX,GetActorLocation());
	GetWorldTimerManager().SetTimer(ChainFXTickTimer, this, &AAI_Ambusher::ChainFXTick, UGameplayStatics::GetWorldDeltaSeconds(this),true);
	OnStartedSlowingPlayer.Broadcast();
}

bool AAI_Ambusher::ExecuteDeath_Implementation(bool KilledByPlayer)
{
	GetWorldTimerManager().ClearTimer(ChainFXTickTimer);
	ChainFXComponent->DestroyComponent();
	return Super::ExecuteDeath_Implementation(KilledByPlayer);
}

void AAI_Ambusher::ChainFXTick()
{
	ChainFXComponent->SetVectorParameter(ChainFXNames.ChainEndLocationName, UGameplayStatics::GetPlayerCharacter(this,0)->GetActorLocation());
	ChainFXComponent->SetVectorParameter(ChainFXNames.ChainStartLocationName, GetMesh()->GetSocketLocation(ChainFXNames.ChainSocketName));
}

void AAI_Ambusher::Disguise() const
{
	DisguiseMesh->SetStaticMesh(MeshToDisguise.Mesh);
	DisguiseMesh->SetMaterial(0,MeshToDisguise.Material);
	GetMesh()->SetVisibility(false,true);
}

void AAI_Ambusher::UnDisguise(AActor* Player)
{
	DisguiseMesh->SetVisibility(false,true);
	GetMesh()->SetVisibility(true,true);
	DisguiseMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	OnPlayerDetected.RemoveAll(this);
}
