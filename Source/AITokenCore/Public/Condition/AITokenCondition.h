// Copyright Lim Young.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AITokenCondition.generated.h"

class UAITokenHolder;
class UAITokenSource;

USTRUCT(BlueprintType)
struct AITOKENCORE_API FAITokenConditionContext
{
	GENERATED_BODY()

	FAITokenConditionContext() = default;

	FAITokenConditionContext(const TObjectPtr<UAITokenSource>& InTokenSource,
	                         const TObjectPtr<UAITokenHolder>& InTokenHolder): TokenSource(InTokenSource),
	                                                                           TokenHolder(InTokenHolder)
	{
	}

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAITokenSource> TokenSource = nullptr;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAITokenHolder> TokenHolder = nullptr;

	bool HasTokenSource() const
	{
		return TokenSource != nullptr;
	}

	bool HasTokenHolder() const
	{
		return TokenHolder != nullptr;
	}

	bool IsValidTokenSourceAndHolder() const
	{
		return HasTokenSource() && HasTokenHolder();
	}
};

/**
 * 
 */
UCLASS(Abstract, DefaultToInstanced, EditInlineNew, Blueprintable, CollapseCategories)
class AITOKENCORE_API UAITokenCondition : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Base")
	bool bReverse = false;

public:
	bool EvaluateCondition(const FAITokenConditionContext& Context) const;

protected:
	UFUNCTION(BlueprintNativeEvent)
	bool Evaluate(const FAITokenConditionContext& Context) const;
};
