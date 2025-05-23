// Copyright Lim Young.


#include "Core/AITokenHolder.h"

void UAITokenHolder::InitTokenHolder(const uint8 InPriority)
{
	Priority = InPriority;
	HeldToken = nullptr;
}

UAIToken* UAITokenHolder::GetHeldToken() const
{
	return HeldToken;
}

bool UAITokenHolder::IsHoldingToken() const
{
	return HeldToken != nullptr;
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

	UAIToken* Token = Source->TakeToken(TokenTag);
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
