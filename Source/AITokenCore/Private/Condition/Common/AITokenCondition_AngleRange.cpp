// Copyright Lim Young.


#include "Condition/Common/AITokenCondition_AngleRange.h"

#include "Condition/AITokenConditionLibrary.h"

bool UAITokenCondition_AngleRange::EvaluateWithActorContext_Implementation(const FAITokenConditionContext& Context,
                                                                           AActor* SourceActor,
                                                                           AActor* HolderActor) const
{
	FVector SourceForward = SourceActor->GetActorForwardVector();
	if (SourceForwardOffsetAngle > 0.f)
	{
		SourceForward = SourceForward.RotateAngleAxis(SourceForwardOffsetAngle, FVector::UpVector);
	}

	const FVector HolderLocation = HolderActor->GetActorLocation();
	const FVector SourceLocation = SourceActor->GetActorLocation();
	FVector SourceToHolderDirection = HolderLocation - SourceLocation;
	if (!bUseZAxis)
	{
		SourceToHolderDirection.Z = 0.f;
	}
	SourceToHolderDirection = SourceToHolderDirection.GetSafeNormal();

	const float AngleWithSourceAndHolder = FMath::RadiansToDegrees(
		FMath::Acos(FVector::DotProduct(SourceForward, SourceToHolderDirection)));

	const bool bResult = UAITokenConditionLibrary::CompareByOperator(AngleWithSourceAndHolder, AngleRangeHalf,
	                                                                 CompareOperator);

#if WITH_EDITOR
	if (bShowDebug)
	{
		DrawDebugSphere(SourceActor->GetWorld(), SourceLocation, 50, 12,
		                FColor::Yellow, false, 3);
		DrawDebugSphere(SourceActor->GetWorld(), SourceLocation, 50, 12,
		                FColor::Blue, false, 3);

		DrawDebugLine(SourceActor->GetWorld(), SourceLocation,
		              SourceLocation + SourceForward.RotateAngleAxis(AngleRangeHalf, FVector::UpVector) * 300.0f,
		              FColor::White, false, 3.0f);
		DrawDebugLine(SourceActor->GetWorld(), SourceLocation,
		              SourceLocation + SourceForward.RotateAngleAxis(-AngleRangeHalf, FVector::UpVector) * 300.0f,
		              FColor::White, false, 3.0f);

		DrawDebugLine(SourceActor->GetWorld(), SourceLocation, HolderLocation,
		              bResult ? FColor::Green : FColor::Red, false, 3.0f);
	}
#endif

	return bResult;
}
