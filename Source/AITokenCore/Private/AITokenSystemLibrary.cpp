// Copyright Lim Young.


#include "AITokenSystemLibrary.h"

bool UAITokenSystemLibrary::AcquireAITokenFromSourceComponent(UAITokenHolderComponent* HolderComponent,
                                                                               UAITokenSourceComponent* SourceComponent,
                                                                               const FGameplayTag TokenTag)
{
	if (!IsValid(HolderComponent) || !IsValid(SourceComponent))
	{
		return false;
	}

	return AcquireAITokenFromSource(HolderComponent->GetAITokenHolder(), SourceComponent->GetAITokenSource(), TokenTag);
}

bool UAITokenSystemLibrary::AcquireAITokenFromSource(UAITokenHolder* Holder, UAITokenSource* Source,
                                                                      const FGameplayTag TokenTag)
{
	if (!IsValid(Holder) || !IsValid(Source))
	{
		return false;
	}

	return Holder->AcquireTokenFromSource(Source, TokenTag);
}

bool UAITokenSystemLibrary::ReleaseAITokenToSourceComponent(UAITokenHolderComponent* HolderComponent)
{
	if (!IsValid(HolderComponent))
	{
		return false;
	}

	return ReleaseAITokenToSource(HolderComponent->GetAITokenHolder());
}

bool UAITokenSystemLibrary::ReleaseAITokenToSource(UAITokenHolder* Holder)
{
	if (!IsValid(Holder))
	{
		return false;
	}

	return Holder->ReleaseHeldToken();
}

bool UAITokenSystemLibrary::LockHeldToken(UAITokenHolderComponent* HolderComponent)
{
	if (IsValid(HolderComponent) && IsValid(HolderComponent->GetAITokenHolder()))
	{
		return HolderComponent->GetAITokenHolder()->LockHeldToken();
	}

	return false;
}

bool UAITokenSystemLibrary::UnlockHeldToken(UAITokenHolderComponent* HolderComponent)
{
	if (IsValid(HolderComponent) && IsValid(HolderComponent->GetAITokenHolder()))
	{
		return HolderComponent->GetAITokenHolder()->UnlockHeldToken();
	}

	return false;
}
