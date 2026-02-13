// Copyright Lim Young.


#include "Condition/AITokenConditionLibrary.h"

bool UAITokenConditionLibrary::TryGetOuterChainActor(const UObject* AITokenHolder,
	AActor*& HolderActor)
{
	UObject* CurrentObject = AITokenHolder->GetOuter();
	if (!IsValid(CurrentObject))
	{
		return false;
	}

	while (!CurrentObject->IsA<UWorld>())
	{
		CurrentObject = CurrentObject->GetOuter();
		if (!IsValid(CurrentObject))
		{
			return false;
		}

		if (CurrentObject->IsA<AActor>())
		{
			HolderActor = Cast<AActor>(CurrentObject);
			return true;
		}
	}

	return false;
}

bool UAITokenConditionLibrary::TryGetAITokenHolderActor(const UAITokenHolder* AITokenHolder,
	AActor*& HolderActor)
{
	if (!IsValid(AITokenHolder))
	{
		return false;
	}
	return TryGetOuterChainActor(AITokenHolder, HolderActor);
}

bool UAITokenConditionLibrary::TryGetAITokenSourceActor(const UAITokenSource* AITokenSource,
	AActor*& SourceActor)
{
	if (!IsValid(AITokenSource))
	{
		return false;
	}
	return TryGetOuterChainActor(AITokenSource, SourceActor);
}