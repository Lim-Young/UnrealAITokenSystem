// Copyright Lim Young.


#include "Core/AIToken.h"

#include "Core/AITokenSource.h"

DEFINE_LOG_CATEGORY(LogAITokenSystem);

UE_DEFINE_GAMEPLAY_TAG_COMMENT(AIToken, "AIToken", "AI token root tag");

void UAIToken::InitToken(const FGameplayTag InTokenTag, UAITokenSource* InOwnerSource)
{
	TokenState = EAITokenState::Free;
	TokenTag = InTokenTag;
	OwnerSource = InOwnerSource;
}

bool UAIToken::AcquireToken(UAITokenHolder* InHolder)
{
	if (TokenState == EAITokenState::Free)
	{
		TokenState = EAITokenState::Held;
		Holder = InHolder;
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
		Holder = nullptr;
		return true;
	}
	return false;
}

UAITokenSource* UAIToken::GetOwnerSource() const
{
	return OwnerSource;
}

UAITokenContainer* UAITokenContainer::NewAITokenContainer(const FGameplayTag TokenTag, const int TokenCount,
                                                          UObject* Outer)
{
	UAITokenContainer* TokenContainer = NewObject<UAITokenContainer>(Outer);
	if (TokenContainer)
	{
		TokenContainer->InitAITokenContainer(TokenTag, TokenCount, CastChecked<UAITokenSource>(Outer));
	}
	return TokenContainer;
}

void UAITokenContainer::InitAITokenContainer(const FGameplayTag TokenTag, const int TokenCount, UAITokenSource* Source)
{
	Tokens.Empty(TokenCount);
	for (int i = 0; i < TokenCount; i++)
	{
		UAIToken* Token = NewObject<UAIToken>(this);
		Token->InitToken(TokenTag, Source);
		Tokens.Add(Token);
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
