// Copyright Lim Young.

#pragma once

#include "CoreMinimal.h"
#include "Condition/AITokenCondition.h"
#include "AITokenCondition_ActorContextBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class AITOKENCORE_API UAITokenCondition_ActorContextBase : public UAITokenCondition
{
	GENERATED_BODY()

protected:
	virtual bool Evaluate_Implementation(const FAITokenConditionContext& Context) const override;

	/**
	 * You Should Override This Function To Implement Your Own Logic, Not Evaluate(...) Function.
	 * @param Context Reference to the current condition context.
	 * @param SourceActor The AiTokenSource Owner Actor.
	 * @param HolderActor The AiTokenHolder Owner Actor.
	 * @return 
	 */
	UFUNCTION(BlueprintNativeEvent)
	bool EvaluateWithActorContext(const FAITokenConditionContext& Context, AActor* SourceActor,
	                              AActor* HolderActor) const;
};
