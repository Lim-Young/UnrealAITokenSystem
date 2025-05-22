// Copyright Blazebone Game Studio


#include "Condition/AITokenConditionPredicate.h"


bool FAITokenConditionPredicate::Evaluate(FAITokenConditionContext Context) const
{
	return true;
}

bool FAITokenConditionPredicate_Single::Evaluate(const FAITokenConditionContext Context) const
{
	if (!IsValid(Condition))
	{
		return false;
	}

	return Condition->EvaluateCondition(Context);
}

bool FAITokenConditionPredicate_And::Evaluate(const FAITokenConditionContext Context) const
{
	if (Predicates.Num() == 0)
	{
		return false;
	}

	bool bResult = true;
	for (auto Predicate : Predicates)
	{
		if (const FAITokenConditionPredicate* AITokenConditionPredicate = Predicate.GetPtr<
			FAITokenConditionPredicate>())
		{
			bResult &= AITokenConditionPredicate->Evaluate(Context);
		}
	}

	return bReverse ? !bResult : bResult;
}

bool FAITokenConditionPredicate_Or::Evaluate(const FAITokenConditionContext Context) const
{
	if (Predicates.Num() == 0)
	{
		return false;
	}

	bool bResult = false;
	for (auto Predicate : Predicates)
	{
		if (const FAITokenConditionPredicate* AITokenConditionPredicate = Predicate.GetPtr<
			FAITokenConditionPredicate>())
		{
			bResult |= AITokenConditionPredicate->Evaluate(Context);
		}
	}

	return bReverse ? !bResult : bResult;
}
