// Copyright Lim Young.

#pragma once

#include "CoreMinimal.h"
#include "AITokenCondition_ActorContextBase.h"
#include "Condition/AITokenConditionEnum.h"
#include "AITokenCondition_AngleRange.generated.h"

/**
 * 
 */
UCLASS(DisplayName = "Angle Range")
class AITOKENCORE_API UAITokenCondition_AngleRange : public UAITokenCondition_ActorContextBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Angle Range", meta = (ClampMin = 0, ClampMax = 360))
	float SourceForwardOffsetAngle = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Angle Range")
	EAITokenConditionMathCompareOperator CompareOperator = EAITokenConditionMathCompareOperator::LessThan;

	UPROPERTY(EditAnywhere, Category = "Angle Range", meta = (ClampMin = 0, ClampMax = 180))
	float AngleRangeHalf = 45.0f;

	UPROPERTY(EditAnywhere, Category = "Angle Range")
	bool bUseZAxis = false;

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category = "Angle Range")
	bool bShowDebug = false;
#endif

	virtual bool EvaluateWithActorContext_Implementation(const FAITokenConditionContext& Context, AActor* SourceActor,
	                                                     AActor* HolderActor) const override;
};
