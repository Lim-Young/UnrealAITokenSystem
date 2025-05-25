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

bool UAITokenSystemLibrary::GetAITokenSourceComponentFromActor(AActor* InActor,
                                                               UAITokenSourceComponent*& OutSourceComponent)
{
	if (!IsValid(InActor))
	{
		return false;
	}

	UAITokenSourceComponent* SourceComponent = InActor->GetComponentByClass<UAITokenSourceComponent>();
	if (!IsValid(SourceComponent))
	{
		return false;
	}

	OutSourceComponent = SourceComponent;
	return true;
}

bool UAITokenSystemLibrary::GetAITokenHolderComponentFromActor(AActor* InActor,
                                                               UAITokenHolderComponent*& OutHolderComponent)
{
	if (!IsValid(InActor))
	{
		return false;
	}

	UAITokenHolderComponent* HolderComponent = InActor->GetComponentByClass<UAITokenHolderComponent>();
	if (!IsValid(HolderComponent))
	{
		return false;
	}

	OutHolderComponent = HolderComponent;
	return true;
}
