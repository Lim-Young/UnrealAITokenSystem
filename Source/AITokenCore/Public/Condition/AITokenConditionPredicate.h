// Copyright Blazebone Game Studio

#pragma once

#include "CoreMinimal.h"
#include "AITokenCondition.h"
#include "StructUtils/InstancedStruct.h"
#include "AITokenConditionPredicate.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct AITOKENCORE_API FAITokenConditionPredicate
{
	GENERATED_BODY()

	virtual ~FAITokenConditionPredicate() = default;


	UPROPERTY(EditAnywhere)
	bool bReverse = false;

	virtual bool Evaluate(FAITokenConditionContext Context) const;
};

USTRUCT()
struct AITOKENCORE_API FAITokenConditionPredicate_Single : public FAITokenConditionPredicate
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Instanced)
	TObjectPtr<UAITokenCondition> Condition = nullptr;

	virtual bool Evaluate(FAITokenConditionContext Context) const override;
};

USTRUCT()
struct AITOKENCORE_API FAITokenConditionPredicate_And : public FAITokenConditionPredicate
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (BaseStruct = "/Script/AITokenCore.AITokenConditionPredicate", ExcludeBasestruct))
	TArray<FInstancedStruct> Predicates;

	virtual bool Evaluate(FAITokenConditionContext Context) const override;
};

USTRUCT()
struct AITOKENCORE_API FAITokenConditionPredicate_Or : public FAITokenConditionPredicate
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (BaseStruct = "/Script/AITokenCore.AITokenConditionPredicate", ExcludeBasestruct))
	TArray<FInstancedStruct> Predicates;

	virtual bool Evaluate(FAITokenConditionContext Context) const override;
};
