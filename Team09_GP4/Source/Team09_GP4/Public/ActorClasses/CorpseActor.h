// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CorpseActor.generated.h"

UCLASS()
class TEAM09_GP4_API ACorpseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACorpseActor();

	UFUNCTION(BlueprintCallable)
	void SetCorpse(USkeletalMesh* SkeletalMeshAsset, UAnimationAsset* NewAnimToPlay);
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* CorpseMesh;

	UPROPERTY(EditDefaultsOnly)
	float CorpseLifeSpan = 8.f;



};
