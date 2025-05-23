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
	virtual void Initialize(const FAITokenConditionContext& Context);
	virtual bool Evaluate(const FAITokenConditionContext& Context) const;
	virtual void Cleanup(const FAITokenConditionContext& Context);
};

UCLASS()
class AITOKENCORE_API UAITokenConditionPredicate_Single : public UAITokenConditionPredicate
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Instanced)
	TObjectPtr<UAITokenCondition> Condition = nullptr;

protected:
	virtual void Initialize(const FAITokenConditionContext& Context) override;
	virtual bool Evaluate(const FAITokenConditionContext& Context) const override;
	virtual void Cleanup(const FAITokenConditionContext& Context) override;
};

UCLASS()
class AITOKENCORE_API UAITokenConditionPredicate_And : public UAITokenConditionPredicate
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Instanced)
	TArray<TObjectPtr<UAITokenConditionPredicate>> Predicates;

	virtual bool Evaluate(const FAITokenConditionContext& Context) const override;
};

UCLASS()
class AITOKENCORE_API UAITokenConditionPredicate_Or : public UAITokenConditionPredicate
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Instanced)
	TArray<TObjectPtr<UAITokenConditionPredicate>> Predicates;

	virtual bool Evaluate(const FAITokenConditionContext& Context) const override;
};
