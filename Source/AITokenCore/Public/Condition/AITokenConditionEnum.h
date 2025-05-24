// Copyright Lim Young.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EAITokenConditionMathCompareOperator : uint8
{
	Equal UMETA(DisplayName = "=="),
	NotEqual UMETA(DisplayName = "!="),
	GreaterThan UMETA(DisplayName = ">"),
	GreaterThanOrEqual UMETA(DisplayName = ">="),
	LessThan UMETA(DisplayName = "<"),
	LessThanOrEqual UMETA(DisplayName = "<="),
};