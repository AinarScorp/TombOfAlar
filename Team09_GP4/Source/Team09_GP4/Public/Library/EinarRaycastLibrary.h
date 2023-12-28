// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EinarRaycastLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TEAM09_GP4_API UEinarRaycastLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, Category = "Raycast",meta =( WorldContext="WorldContextObject", AutoCreateRefTerm="ActorsToIgnore"))
	static bool ConeCastByChannel(const UObject* WorldContextObject, FVector Start, FVector Direction,FVector ConeNormal,float Radius,int RayCount,float VisionAngle,ETraceTypeQuery TraceTypeQuery, const TArray<AActor*>& ActorsToIgnore,EDrawDebugTrace::Type DrawDebug,TArray<FHitResult>& HitResults);

};
