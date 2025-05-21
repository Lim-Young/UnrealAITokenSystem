// Copyright Lim Young.


#include "Core/AITokenSource.h"

void UAITokenSource::AddOrResetToken(const FGameplayTag& TokenTag, const int TokenCount)
{
	if (Tokens.Contains(TokenTag) || !Tokens[TokenTag])
	{
		Tokens[TokenTag]->ReleaseAllToken();;
	}

	Tokens.Emplace(TokenTag, UAITokenContainer::NewAITokenContainer(TokenTag, TokenCount, this));
}

void UAITokenSource::InitTokenSource(const FAITokenSourceDefinition& TokenSourceDefinition)
{
	for (const auto& SourceToken : TokenSourceDefinition.SourceTokens)
	{
		if (IsValid(SourceToken.Key) && SourceToken.Value > 0)
		{
			AddOrResetToken(SourceToken.Key.Get()->TokenTag, SourceToken.Value);
		}
	}
}

bool UAITokenSource::TakeToken(UAITokenHolder* TokenHolder, const FGameplayTag& TokenTag)
{
	if (!IsValid(TokenHolder))
	{
		return false;
	}

	if (!Tokens.Contains(TokenTag) || !Tokens[TokenTag])
	{
		return false;
	}

	UAIToken* Token = nullptr;
	if (Tokens[TokenTag]->TryGetFreeToken(Token))
	{
		Token->AcquireToken(TokenHolder);
		return true;
	}
	else
	{
		// TODO: Try to preempt token
	}

	return false;
}

bool UAITokenSource::ReturnToken(UAITokenHolder* TokenHolder, const FGameplayTag& TokenTag, const int TokenCount)
{
	if (!TokenHolder || !TokenHolder->IsHoldingToken())
	{
		return false;
	}

	TokenHolder->GetHeldToken()->ReleaseToken();
	return true;
}
