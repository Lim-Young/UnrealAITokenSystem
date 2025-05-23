// Copyright Lim Young.


#include "Core/AITokenSource.h"
#include "Core/AITokenHolder.h"

void UAITokenSource::AddOrResetToken(UAITokenData* TokenData, const int TokenCount)
{
	if (!IsValid(TokenData))
	{
		UE_LOG(LogAITokenSystem, Warning, TEXT("Invalid TokenData provided to AddOrResetToken"));
		return;
	}

	if (Tokens.Contains(TokenData->TokenTag) && Tokens.Find(TokenData->TokenTag))
	{
		Tokens[TokenData->TokenTag]->ReleaseAllToken();;
	}

	Tokens.Emplace(TokenData->TokenTag, UAITokenContainer::NewAITokenContainer(TokenData, TokenCount, this));
}

void UAITokenSource::InitTokenSource(const FAITokenSourceDefinition& TokenSourceDefinition)
{
	Tokens.Empty();

	for (const auto& SourceToken : TokenSourceDefinition.SourceTokens)
	{
		if (IsValid(SourceToken.Key) && SourceToken.Value > 0)
		{
			AddOrResetToken(SourceToken.Key, SourceToken.Value);
		}
	}
}

UAIToken* UAITokenSource::TakeToken(const FGameplayTag& TokenTag)
{
	if (!Tokens.Contains(TokenTag))
	{
		return nullptr;
	}

	if (!IsValid(Tokens[TokenTag]))
	{
		return nullptr;
	}

	UAIToken* Token = nullptr;
	if (Tokens[TokenTag]->TryGetFreeToken(Token))
	{
		return Token;
	}

	// TODO: Try to preempt token
	TArray<UAIToken*> TokensToPreempt;
	if (Tokens[TokenTag]->TryGetAllHeldToken(TokensToPreempt))
	{
		for (UAIToken* TokenToPreempt : TokensToPreempt)
		{
			if (TokenToPreempt->GetHolder()->ReleaseHeldToken())
			{
				return TokenToPreempt;
			}
		}
	}

	return nullptr;
}
