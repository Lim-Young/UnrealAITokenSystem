// Copyright Blazebone Game Studio

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
};

/**
 * 
 */
UCLASS(Abstract, DefaultToInstanced, EditInlineNew)
class AITOKENCORE_API UAITokenCondition : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	bool EvaluateCondition(FAITokenConditionContext Context) const;
};
