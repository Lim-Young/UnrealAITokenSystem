// Copyright Blazebone Game Studio

#pragma once

#include "CoreMinimal.h"
#include "AITokenCondition.h"
#include "AITokenConditionPredicate.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, DefaultToInstanced, EditInlineNew)
class AITOKENCORE_API UAITokenConditionPredicate : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	bool bReverse = false;

public:
	virtual bool Evaluate(FAITokenConditionContext Context) const;
};

UCLASS()
class AITOKENCORE_API UAITokenConditionPredicate_Single : public UAITokenConditionPredicate
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Instanced)
	TObjectPtr<UAITokenCondition> Condition = nullptr;

	virtual bool Evaluate(FAITokenConditionContext Context) const override;
};

UCLASS()
class AITOKENCORE_API UAITokenConditionPredicate_And : public UAITokenConditionPredicate
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Instanced)
	TArray<TObjectPtr<UAITokenConditionPredicate>> Predicates;

	virtual bool Evaluate(FAITokenConditionContext Context) const override;
};

UCLASS()
class AITOKENCORE_API UAITokenConditionPredicate_Or : public UAITokenConditionPredicate
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Instanced)
	TArray<TObjectPtr<UAITokenConditionPredicate>> Predicates;

	virtual bool Evaluate(FAITokenConditionContext Context) const override;
};
