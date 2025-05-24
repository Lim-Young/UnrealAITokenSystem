// Copyright Lim Young.

#pragma once

#include "CoreMinimal.h"
#include "AITokenCondition_ActorContextBase.h"
#include "Condition/AITokenConditionEnum.h"
#include "AITokenCondition_Distance.generated.h"

/**
 * Condition to check the distance between source and holder.
 */
UCLASS(DisplayName = "Distance")
class AITOKENCORE_API UAITokenCondition_Distance : public UAITokenCondition_ActorContextBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Distance")
	EAITokenConditionMathCompareOperator CompareOperator = EAITokenConditionMathCompareOperator::Equal;

	UPROPERTY(EditAnywhere, Category = "Distance")
	float Distance = 600.0f;

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool bShowDebug = false;
#endif

	virtual bool EvaluateWithActorContext_Implementation(const FAITokenConditionContext& Context, AActor* SourceActor,
	                                                     AActor* HolderActor) const override;
};
