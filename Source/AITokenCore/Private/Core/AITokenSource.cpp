// Copyright Lim Young.


#include "Core/AITokenSource.h"
#include "Core/AITokenHolder.h"

void UAITokenSource::AddOrResetToken(UAITokenData* TokenData, const int TokenCount)
{
	if (!IsValid(TokenData))
	{
		return;
	}

	if (Tokens.Contains(TokenData->TokenTag) && Tokens.Find(TokenData->TokenTag))
	{
		Tokens[TokenData->TokenTag]->ReleaseAllToken();;
	}

	Tokens.Emplace(TokenData->TokenTag, UAITokenContainer::NewAITokenContainer(TokenData, TokenCount, this));
}

void UAITokenSource::CreatePreemptTestToken(const TObjectPtr<UAITokenData>& TokenData)
{
	if (!IsValid(TokenData))
	{
		return;
	}

	if (PreemptTestTokens.Contains(TokenData->TokenTag) && PreemptTestTokens.Find(TokenData->TokenTag))
	{
		return;
	}

	UAIToken* PreemptTestToken = NewObject<UAIToken>(this);
	PreemptTestToken->InitToken(TokenData, this);
	PreemptTestTokens.Emplace(TokenData->TokenTag, PreemptTestToken);
}

void UAITokenSource::InitTokenSource(const FAITokenSourceDefinition& TokenSourceDefinition)
{
	Tokens.Empty();

	for (const auto& SourceToken : TokenSourceDefinition.SourceTokens)
	{
		if (IsValid(SourceToken.Key) && SourceToken.Value > 0)
		{
			AddOrResetToken(SourceToken.Key, SourceToken.Value);
			CreatePreemptTestToken(SourceToken.Key);
		}
	}
}

UAIToken* UAITokenSource::TakeToken(const FGameplayTag& TokenTag, UAITokenHolder* Holder)
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
	if (Tokens[TokenTag]->TryGetCanAcquireToken(Holder, Token))
	{
		return Token;
	}

	// Check holder can preempt the token
	if (!Holder->TokenHolderConfig.bAllowPreempt)
	{
		return nullptr;
	}

	if (PreemptTestTokens.Contains(TokenTag) && PreemptTestTokens[TokenTag])
	{
		UAIToken* PreemptTestToken = PreemptTestTokens[TokenTag];
		PreemptTestToken->Holder = Holder;

		if (!PreemptTestToken->CheckPreemptCondition(FAITokenConditionContext(this, Holder)))
		{
			return nullptr;
		}
	}
	else
	{
		// Under normal circumstances, if a corresponding TokenTag Key exists in the Tokens Map,
		// then it should also exist in the PreemptTestTokens Map.
		checkNoEntry();
		return nullptr;
	}

	// Preempt token
	// Doesn't need to check if the holder is valid, because we already checked it in TryGetCanAcquireToken
	TArray<UAIToken*> TokensToPreempt;
	if (Tokens[TokenTag]->TryGetAllCanPreemptTokens(Holder, TokensToPreempt))
	{
		const int32 NumTokensToPreempt = TokensToPreempt.Num();
		if (NumTokensToPreempt == 0)
		{
			return nullptr;
		}

		UAIToken* TokenToPreempt = nullptr;
		switch (Holder->TokenHolderConfig.PreemptResultChooseType)
		{
		case EAITokenPreemptResultChooseType::FirstMatch:
			TokenToPreempt = TokensToPreempt[0];
			break;
		case EAITokenPreemptResultChooseType::Random:
			TokenToPreempt = TokensToPreempt[FMath::RandRange(0, NumTokensToPreempt - 1)];
			break;
		default:
			break;
		}

		if (TokenToPreempt->GetHolder()->ReleaseHeldToken())
		{
			return TokenToPreempt;
		}
		// Because if the token can be preempted, it must be held by a holder.
		// Only the token in EAITokenState::Locked state cannot be released.
		checkNoEntry();
	}

	return nullptr;
}
