// Copyright Blazebone Game Studio

#pragma once

#include "CoreMinimal.h"
#include "Condition/AITokenCondition.h"
#include "AITokenCondition_RandomBool.generated.h"

/**
 * Use this condition to randomly return true or false based on a specified probability.
 */
UCLASS(DisplayName = "Random Bool Condition")
class AITOKENCORE_API UAITokenCondition_RandomBool : public UAITokenCondition
{
	GENERATED_BODY()

	FRandomStream RandomStream;

protected:
	UPROPERTY(EditAnywhere, Category = "RandomBool", meta = (ClampMin = 0, ClampMax = 1))
	float Probability = 0.5f;

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool bDrawDebug = false;
#endif

	UAITokenCondition_RandomBool();
	virtual bool Evaluate_Implementation(const FAITokenConditionContext& Context) const override;

#if WITH_EDITOR
	void DrawDebugContent(const FAITokenConditionContext& Context, bool bSuccess) const;
#endif
};
