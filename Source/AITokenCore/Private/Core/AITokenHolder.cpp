// Copyright Lim Young.


#include "Core/AITokenHolder.h"

void UAITokenHolder::InitTokenHolder(const uint8 InPriority)
{
	Priority = InPriority;
	HeldToken = nullptr;
}

void UAITokenHolder::HoldToken(UAIToken* InToken)
{
	HeldToken = InToken;
}

void UAITokenHolder::ReleaseToken()
{
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
