// Copyright Lim Young.


#include "AIToken.h"

UE_DEFINE_GAMEPLAY_TAG_COMMENT(AIToken, "AIToken", "AI token root tag");

bool UAIToken::AcquireToken(UAITokenHolder* InHolder)
{
	if (TokenState == EAITokenState::Free)
	{
		TokenState = EAITokenState::Held;
		Holder = InHolder;
		Holder->HoldToken(this);
		return true;
	}
	return false;
}

bool UAIToken::LockToken(UAITokenHolder* InHolder)
{
	if (TokenState == EAITokenState::Held && Holder == InHolder)
	{
		TokenState = EAITokenState::Locked;
		return true;
	}
	return false;
}

bool UAIToken::PreemptToken(UAITokenHolder* InHolder)
{
	// if (TokenState == EAITokenState::Held && Holder == InHolder)
	// {
	// 	TokenState = EAITokenState::Free;
	// 	Holder = nullptr;
	// 	return true;
	// }
	// return false;
	return true;
}

bool UAIToken::ReleaseToken()
{
	if (TokenState != EAITokenState::Free)
	{
		TokenState = EAITokenState::Free;
		if (Holder)
		{
			Holder->ReleaseToken();
		}
		Holder = nullptr;
		return true;
	}
	return false;
}

UAITokenContainer* UAITokenContainer::NewAITokenContainer(const FGameplayTag TokenTag, const int TokenCount,
	UObject* Outer)
{
	UAITokenContainer* TokenContainer = NewObject<UAITokenContainer>(Outer);
	if (TokenContainer)
	{
		TokenContainer->InitAITokenContainer(TokenTag, TokenCount);
	}
	return TokenContainer;
}

void UAITokenContainer::InitAITokenContainer(const FGameplayTag TokenTag, const int TokenCount)
{
	Tokens.SetNum(TokenCount);
	for (int i = 0; i < TokenCount; i++)
	{
		Tokens[i]->TokenTag = TokenTag;
		Tokens[i]->TokenState = EAITokenState::Free;
	}
}

void UAITokenContainer::ReleaseAllToken()
{
	if (Tokens.Num() == 0)
	{
		return;
	}

	for (UAIToken* Token : Tokens)
	{
		if (IsValid(Token))
		{
			Token->ReleaseToken();
		}
	}
}

bool UAITokenContainer::TryGetFreeToken(UAIToken*& OutToken)
{
	for (UAIToken* Token : Tokens)
	{
		if (IsValid(Token) && Token->TokenState == EAITokenState::Free)
		{
			OutToken = Token;
			return true;
		}
	}
	return false;
}
