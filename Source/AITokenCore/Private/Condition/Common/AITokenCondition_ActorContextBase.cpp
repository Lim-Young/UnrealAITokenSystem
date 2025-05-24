// Copyright Lim Young.


#include "Condition/Common/AITokenCondition_ActorContextBase.h"

#include "Condition/AITokenConditionLibrary.h"

bool UAITokenCondition_ActorContextBase::Evaluate_Implementation(const FAITokenConditionContext& Context) const
{
	if (!Context.IsValidTokenSourceAndHolder())
	{
		return false;
	}

	AActor* AITokenSourceActor = nullptr;
	AActor* AITokenHolderActor = nullptr;
	if (!UAITokenConditionLibrary::TryGetAITokenSourceActor(Context.TokenSource, AITokenSourceActor) ||
		!UAITokenConditionLibrary::TryGetAITokenHolderActor(Context.TokenHolder, AITokenHolderActor))
	{
		return false;
	}

	return EvaluateWithActorContext(Context, AITokenSourceActor, AITokenHolderActor);
}

bool UAITokenCondition_ActorContextBase::EvaluateWithActorContext_Implementation(const FAITokenConditionContext& Context,
                                                                          AActor* SourceActor,
                                                                          AActor* HolderActor) const
{
	return true;
}
