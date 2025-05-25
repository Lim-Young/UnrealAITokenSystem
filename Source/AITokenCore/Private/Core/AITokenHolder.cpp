// Copyright Lim Young.


#include "Core/AITokenHolder.h"

void UAITokenHolder::InitTokenHolder(const FAITokenHolderConfig& InTokenHolderConfig)
{
	TokenHolderConfig = InTokenHolderConfig;
	HeldToken = nullptr;
}

UAIToken* UAITokenHolder::GetHeldToken() const
{
	return HeldToken;
}

bool UAITokenHolder::IsHoldingToken() const
{
	return IsValid(HeldToken.Get());
}

bool UAITokenHolder::AcquireTokenFromSource(UAITokenSource* Source, const FGameplayTag& TokenTag)
{
	if (!IsValid(Source))
	{
		return false;
	}

	if (IsHoldingToken())
	{
		if (HeldToken->TokenTag == TokenTag)
		{
			UE_LOG(LogAITokenSystem, Verbose, TEXT("Token %s is already held by this holder."), *HeldToken->GetName());
			return true;
		}

		if (!ReleaseHeldToken())
		{
			UE_LOG(LogAITokenSystem, Verbose, TEXT("Failed to release held token %s."), *HeldToken->GetName());
			return false;
		}
	}

	UAIToken* Token = Source->TakeToken(TokenTag, this);
	if (IsValid(Token))
	{
		if (Token->GrantedTo(this))
		{
			HeldToken = Token;
			return true;
		}

		UE_LOG(LogAITokenSystem, Verbose, TEXT("Failed to acquire token %s."), *Token->GetName());
	}

	return false;
}

bool UAITokenHolder::ReleaseHeldToken()
{
	if (!IsValid(HeldToken))
	{
		return true;
	}

	if (HeldToken->Release())
	{
		HeldToken = nullptr;
		return true;
	}

	UE_LOG(LogAITokenSystem, Verbose, TEXT("Failed to release held token %s."), *HeldToken->GetName());
	return false;
}

bool UAITokenHolder::LockHeldToken() const
{
	if (!IsHoldingToken())
	{
		UE_LOG(LogAITokenSystem, Verbose, TEXT("No token held to lock."));
		return false;
	}

	if (HeldToken->LockToken())
	{
		return true;
	}

	return false;
}

bool UAITokenHolder::UnlockHeldToken() const
{
	if (!IsHoldingToken())
	{
		UE_LOG(LogAITokenSystem, Verbose, TEXT("No token held to unlock."));
		return false;
	}

	if (HeldToken->UnlockToken())
	{
		return true;
	}

	return false;
}
