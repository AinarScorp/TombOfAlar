// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorClasses/CorpseActor.h"

ACorpseActor::ACorpseActor()
{
	PrimaryActorTick.bCanEverTick = false;

	CorpseMesh = CreateDefaultSubobject<USkeletalMeshComponent>("CorpseMesh");
	CorpseMesh->SetVisibility(false);
	SetRootComponent(CorpseMesh);
}

void ACorpseActor::SetCorpse(USkeletalMesh* SkeletalMeshAsset, UAnimationAsset* NewAnimToPlay)
{
	CorpseMesh->SetSkeletalMeshAsset(SkeletalMeshAsset);
	CorpseMesh->SetAnimation(NewAnimToPlay);
	CorpseMesh->SetVisibility(true);
	SetLifeSpan(CorpseLifeSpan);
}

