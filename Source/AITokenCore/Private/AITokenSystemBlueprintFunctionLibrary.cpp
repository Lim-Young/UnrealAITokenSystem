// Copyright Blazebone Game Studio


#include "AITokenSystemBlueprintFunctionLibrary.h"

bool UAITokenSystemBlueprintFunctionLibrary::AcquireAITokenFromSourceComponent(UAITokenHolderComponent* HolderComponent,
                                                                               UAITokenSourceComponent* SourceComponent,
                                                                               const FGameplayTag TokenTag)
{
	if (!IsValid(HolderComponent) || !IsValid(SourceComponent))
	{
		return false;
	}

	return AcquireAITokenFromSource(HolderComponent->GetAITokenHolder(), SourceComponent->GetAITokenSource(), TokenTag);
}

bool UAITokenSystemBlueprintFunctionLibrary::AcquireAITokenFromSource(UAITokenHolder* Holder, UAITokenSource* Source,
                                                                      const FGameplayTag TokenTag)
{
	if (!IsValid(Holder) || !IsValid(Source))
	{
		return false;
	}

	return Holder->AcquireTokenFromSource(Source, TokenTag);
}

bool UAITokenSystemBlueprintFunctionLibrary::ReleaseAITokenToSourceComponent(UAITokenHolderComponent* HolderComponent)
{
	if (!IsValid(HolderComponent))
	{
		return false;
	}

	return ReleaseAITokenToSource(HolderComponent->GetAITokenHolder());
}

bool UAITokenSystemBlueprintFunctionLibrary::ReleaseAITokenToSource(UAITokenHolder* Holder)
{
	if (!IsValid(Holder))
	{
		return false;
	}

	return Holder->ReleaseHeldToken();
}

bool UAITokenSystemBlueprintFunctionLibrary::LockHeldToken(UAITokenHolderComponent* HolderComponent)
{
	if (IsValid(HolderComponent) && IsValid(HolderComponent->GetAITokenHolder()))
	{
		return HolderComponent->GetAITokenHolder()->LockHeldToken();
	}

	return false;
}

bool UAITokenSystemBlueprintFunctionLibrary::UnlockHeldToken(UAITokenHolderComponent* HolderComponent)
{
	if (IsValid(HolderComponent) && IsValid(HolderComponent->GetAITokenHolder()))
	{
		return HolderComponent->GetAITokenHolder()->UnlockHeldToken();
	}

	return false;
}
