// Copyright Lim Young.

#pragma once

#include "CoreMinimal.h"
#include "AITokenConditionEnum.h"
#include "Core/AITokenHolder.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AITokenConditionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class AITOKENCORE_API UAITokenConditionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

private:
	static bool TryGetOuterChainActor(const UObject* AITokenHolder, AActor*& HolderActor);

public:
	UFUNCTION(BlueprintCallable, Category = "AITokenCondition")
	static bool TryGetAITokenHolderActor(const UAITokenHolder* AITokenHolder, AActor*& HolderActor);

	UFUNCTION(BlueprintCallable, Category = "AITokenCondition")
	static bool TryGetAITokenSourceActor(const UAITokenSource* AITokenSource, AActor*& SourceActor);

	template <typename T>
	static bool CompareByOperator(const T& A, const T& B, const EAITokenConditionMathCompareOperator Operator);
};
