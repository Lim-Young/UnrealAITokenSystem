// Copyright Blazebone Game Studio


#include "Condition/Common/AITokenCondition_RandomBool.h"

#include "Condition/AITokenConditionLibrary.h"
#include "Core/AITokenSource.h"

UAITokenCondition_RandomBool::UAITokenCondition_RandomBool()
{
	RandomStream = FRandomStream();
	RandomStream.GenerateNewSeed();
}

bool UAITokenCondition_RandomBool::Evaluate_Implementation(const FAITokenConditionContext& Context) const
{
	if (Probability == 0)
	{
#if WITH_EDITOR
		DrawDebugContent(Context, false);
#endif
		return false;
	}

	if (Probability == 1)
	{
#if WITH_EDITOR
		DrawDebugContent(Context, true);
#endif
		return true;
	}

	const bool bResult = RandomStream.FRand() <= Probability;
#if WITH_EDITOR
	DrawDebugContent(Context, bResult);
#endif
	return bResult;
}

#if WITH_EDITOR
void UAITokenCondition_RandomBool::DrawDebugContent(const FAITokenConditionContext& Context, bool bSuccess) const
{
	if (bDrawDebug)
	{
		AActor* AITokenSourceActor = nullptr;
		AActor* AITokenHolderActor = nullptr;
		UAITokenConditionLibrary::TryGetAITokenSourceActor(Context.TokenSource, AITokenSourceActor);
		UAITokenConditionLibrary::TryGetAITokenHolderActor(Context.TokenHolder, AITokenHolderActor);
		if (IsValid(AITokenSourceActor) && IsValid(AITokenHolderActor))
		{
			DrawDebugLine(AITokenSourceActor->GetWorld(),
			              AITokenSourceActor->GetActorLocation(),
			              AITokenHolderActor->GetActorLocation(),
			              bSuccess ? FColor::Green : FColor::Red,
			              false, 3.0f);
		}
	}
}
#endif
