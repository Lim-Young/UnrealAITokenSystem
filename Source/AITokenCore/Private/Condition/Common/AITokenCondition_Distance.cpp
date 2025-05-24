// Copyright Lim Young.


#include "Condition/Common/AITokenCondition_Distance.h"

#include "Condition/AITokenConditionLibrary.h"

bool UAITokenCondition_Distance::EvaluateWithActorContext_Implementation(const FAITokenConditionContext& Context,
                                                                         AActor* SourceActor, AActor* HolderActor) const
{
	const float CurrentDistance = FVector::Distance(SourceActor->GetActorLocation(),
	                                                HolderActor->GetActorLocation());

	const bool bResult = UAITokenConditionLibrary::CompareByOperator(CurrentDistance, Distance, CompareOperator);
#if WITH_EDITOR
	if (bShowDebug)
	{
		DrawDebugSphere(SourceActor->GetWorld(), SourceActor->GetActorLocation(), 50, 12,
		                FColor::Yellow, false, 3);
		DrawDebugSphere(HolderActor->GetWorld(), HolderActor->GetActorLocation(), 50, 12,
		                FColor::Blue, false, 3);
		DrawDebugLine(SourceActor->GetWorld(), SourceActor->GetActorLocation(),
		              HolderActor->GetActorLocation(),
		              bResult ? FColor::Green : FColor::Red, false, 3);
	}
#endif

	return bResult;
}
