// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/EinarRaycastLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

bool UEinarRaycastLibrary::ConeCastByChannel(const UObject* WorldContextObject, FVector Start, FVector Direction,FVector ConeNormal,float Radius,int RayCount,float VisionAngle,ETraceTypeQuery TraceTypeQuery, const TArray<AActor*>& ActorsToIgnore,EDrawDebugTrace::Type DrawDebug,TArray<FHitResult>& HitResults)
{
	for (int r = 0; r <= RayCount; ++r)
	{
		float Angle = float(r)/float(RayCount) * VisionAngle;
		FVector End =UKismetMathLibrary::RotateAngleAxis(Direction,Angle, ConeNormal) * Radius;
		End += Start;
		//FVector End = Direction * Radius;
		FHitResult OutHitResult;
		bool SuccessfulHit = UKismetSystemLibrary::LineTraceSingle(
			WorldContextObject,Start, End, TraceTypeQuery,false,
			ActorsToIgnore,DrawDebug,OutHitResult,true);
		if (SuccessfulHit)
		{
			HitResults.Add(OutHitResult);
		}
		Angle *=-1;
		End = UKismetMathLibrary::RotateAngleAxis(Direction,Angle, ConeNormal)* Radius;
		End+=Start;
		//End = Direction * Radius;
		SuccessfulHit = UKismetSystemLibrary::LineTraceSingle(
			WorldContextObject,Start, End, TraceTypeQuery,false,
			ActorsToIgnore,DrawDebug,OutHitResult,true);
		if (SuccessfulHit)
		{
			HitResults.Add(OutHitResult);
		}
	}
	return !HitResults.IsEmpty();
}
