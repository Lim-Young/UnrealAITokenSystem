// Copyright Lim Young.


#include "Core/AIToken.h"

#include "Core/AITokenHolder.h"
#include "Core/AITokenSource.h"

DEFINE_LOG_CATEGORY(LogAITokenSystem);

UE_DEFINE_GAMEPLAY_TAG_COMMENT(AIToken, "AIToken", "AI token root tag");

void UAIToken::InitToken(const FGameplayTag InTokenTag, UAITokenSource* InOwnerSource)
{
	TokenState = EAITokenState::Free;
	TokenTag = InTokenTag;
	OwnerSource = InOwnerSource;
}

bool UAIToken::GrantedTo(UAITokenHolder* InHolder)
{
	if (TokenState == EAITokenState::Free)
	{
		TokenState = EAITokenState::Held;
		Holder = InHolder;
		return true;
	}
	return false;
}

bool UAIToken::LockToken()
{
	if (!HasHolder())
	{
		UE_LOG(LogAITokenSystem, Verbose, TEXT("LockToken failed: Token has no holder"));
		return false;
	}

	if (TokenState == EAITokenState::Locked)
	{
		UE_LOG(LogAITokenSystem, Verbose, TEXT("Token is already locked"));
		return true;
	}

	if (TokenState == EAITokenState::Held)
	{
		TokenState = EAITokenState::Locked;
		return true;
	}

	return false;
}

bool UAIToken::UnlockToken()
{
	if (TokenState == EAITokenState::Locked)
	{
		// Because the token is locked, so we can sure that the token has a holder
		check(HasHolder())

		TokenState = EAITokenState::Held;
		return true;
	}

	UE_LOG(LogAITokenSystem, Verbose, TEXT("UnlockToken failed: Token is not locked"));
	return false;
}

// bool UAIToken::PreemptToken(UAITokenHolder* InHolder)
// {
// 	// if (TokenState == EAITokenState::Held && Holder == InHolder)
// 	// {
// 	// 	TokenState = EAITokenState::Free;
// 	// 	Holder = nullptr;
// 	// 	return true;
// 	// }
// 	// return false;
// 	return true;
// }

bool UAIToken::Release()
{
	if (TokenState == EAITokenState::Locked)
	{
		UE_LOG(LogAITokenSystem, Verbose, TEXT("Token is locked, cannot release"));
		return false;
	}

	if (TokenState == EAITokenState::Held)
	{
		TokenState = EAITokenState::Free;
		Holder = nullptr;
		return true;
	}

	UE_LOG(LogAITokenSystem, Verbose, TEXT("Token is not held, cannot release"));
	return false;
}

UAITokenSource* UAIToken::GetOwnerSource() const
{
	return OwnerSource;
}

UAITokenHolder* UAIToken::GetHolder() const
{
	return Holder;
}

bool UAIToken::HasHolder() const
{
	return IsValid(Holder.Get());
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
		UAIToken* Token = NewObject<UAIToken>(Source);
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
			if (Token->HasHolder())
			{
				if (Token->TokenState == EAITokenState::Locked)
				{
					Token->GetHolder()->UnlockHeldToken();
				}

				Token->GetHolder()->ReleaseHeldToken();
			}
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

bool UAITokenContainer::TryGetAllHeldToken(TArray<UAIToken*>& OutTokens)
{
	TArray<UAIToken*> HeldTokens;

	for (UAIToken* Token : Tokens)
	{
		if (IsValid(Token) && Token->TokenState == EAITokenState::Held)
		{
			HeldTokens.Add(Token);
		}
	}

	if (HeldTokens.Num() > 0)
	{
		OutTokens = HeldTokens;
		return true;
	}

	return false;
}
