// Copyright Blazebone Game Studio


#include "Condition/AITokenConditionPredicate.h"


bool UAITokenConditionPredicate::Evaluate(FAITokenConditionContext Context) const
{
	return true;
}

bool UAITokenConditionPredicate_Single::Evaluate(const FAITokenConditionContext Context) const
{
	if (!IsValid(Condition))
	{
		return false;
	}

	return Condition->EvaluateCondition(Context);
}

bool UAITokenConditionPredicate_And::Evaluate(const FAITokenConditionContext Context) const
{
	if (Predicates.Num() == 0)
	{
		return false;
	}

	bool bResult = true;
	for (auto Predicate : Predicates)
	{
		if (IsValid(Predicate))
		{
			bResult &= Predicate->Evaluate(Context);
		}
	}

	return bReverse ? !bResult : bResult;
}

bool UAITokenConditionPredicate_Or::Evaluate(const FAITokenConditionContext Context) const
{
	if (Predicates.Num() == 0)
	{
		return false;
	}

	bool bResult = false;
	for (auto Predicate : Predicates)
	{
		if (IsValid(Predicate))
		{
			bResult |= Predicate->Evaluate(Context);
		}
	}

	return bReverse ? !bResult : bResult;
}
