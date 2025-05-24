// Copyright Lim Young.


#include "Condition/AITokenCondition.h"

bool UAITokenCondition::EvaluateCondition(const FAITokenConditionContext& Context) const
{
	return bReverse ? !Evaluate_Implementation(Context) : Evaluate_Implementation(Context);
}

bool UAITokenCondition::Evaluate_Implementation(const FAITokenConditionContext& Context) const
{
	return true;
}
