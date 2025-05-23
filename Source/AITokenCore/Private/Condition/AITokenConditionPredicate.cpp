// Copyright Blazebone Game Studio


#include "Condition/AITokenConditionPredicate.h"


void UAITokenConditionPredicate::Initialize(const FAITokenConditionContext& Context)
{
}

bool UAITokenConditionPredicate::Evaluate(const FAITokenConditionContext& Context) const
{
	return true;
}

void UAITokenConditionPredicate::Cleanup(const FAITokenConditionContext& Context)
{
}

void UAITokenConditionPredicate_Single::Initialize(const FAITokenConditionContext& Context)
{
	if (!IsValid(Condition))
	{
		return;
	}

	Condition->Initialize(Context);
}

bool UAITokenConditionPredicate_Single::Evaluate(const FAITokenConditionContext& Context) const
{
	if (!IsValid(Condition))
	{
		return false;
	}

	return Condition->EvaluateCondition(Context);
}

void UAITokenConditionPredicate_Single::Cleanup(const FAITokenConditionContext& Context)
{
	if (!IsValid(Condition))
	{
		return;
	}

	Condition->Cleanup(Context);
}

bool UAITokenConditionPredicate_And::Evaluate(const FAITokenConditionContext& Context) const
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

bool UAITokenConditionPredicate_Or::Evaluate(const FAITokenConditionContext& Context) const
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
