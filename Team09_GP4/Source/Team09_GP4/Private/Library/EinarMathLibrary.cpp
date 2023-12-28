// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/EinarMathLibrary.h"

#include "Kismet/KismetMathLibrary.h"

float UEinarMathLibrary::GetAngleBetweenVectors(FVector VectorA, FVector VectorB, bool GetInDeg)
{
	VectorA.Normalize();
	VectorB.Normalize();
	const float DotProduct = UKismetMathLibrary::Dot_VectorVector(VectorA, VectorB);
	return GetInDeg ? UKismetMathLibrary::DegAcos(DotProduct) : UKismetMathLibrary::Acos(DotProduct);
}

void UEinarMathLibrary::DirectionToVector(FVector FromVector, FVector ToVector, bool Normalize, FVector& OutVector,float& NonNormLength)
{
	FVector NonNormDirection = ToVector - FromVector;
	OutVector = Normalize ? NonNormDirection.GetSafeNormal() : NonNormDirection;
	NonNormLength = NonNormDirection.Length();
}

void UEinarMathLibrary::DirectionToActor(AActor* ThisActor, AActor* TargetActor, bool Normalize, FVector& OutVector,float& NonNormLength)
{
	if (!ThisActor || !TargetActor)
	{
		return;
	}
	DirectionToVector(ThisActor->GetActorLocation(), TargetActor->GetActorLocation(), Normalize, OutVector, NonNormLength);
}

FVector UEinarMathLibrary::GetMovementOffsetVector(APawn* Pawn,float YawOffset)
{
	if (!Pawn) return FVector::Zero();

	FRotator OffsetRotation = UKismetMathLibrary::NormalizedDeltaRotator(Pawn->GetActorRotation(), UKismetMathLibrary::MakeRotFromX(Pawn->GetVelocity()));
	OffsetRotation.Pitch = 0;
	OffsetRotation.Roll = 0;

	return UKismetMathLibrary::GetForwardVector(OffsetRotation);
	
}


