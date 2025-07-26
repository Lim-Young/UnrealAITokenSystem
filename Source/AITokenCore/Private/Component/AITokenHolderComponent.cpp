// Copyright Lim Young.


#include "Component/AITokenHolderComponent.h"


// Sets default values for this component's properties
UAITokenHolderComponent::UAITokenHolderComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UAITokenHolderComponent::BeginPlay()
{
	InitAITokenHolder();

	Super::BeginPlay();
}

void UAITokenHolderComponent::InitAITokenHolder()
{
	if (!AITokenHolder)
	{
		AITokenHolder = NewObject<UAITokenHolder>(this);
		check(AITokenHolder);

		AITokenHolder->InitTokenHolder(AITokenHolderConfig);
	}
}

UAITokenHolder* UAITokenHolderComponent::GetAITokenHolder() const
{
	return AITokenHolder;
}

FGameplayTag UAITokenHolderComponent::GetHeldTokenTag() const
{
	if (IsValid(AITokenHolder))
	{
		if (const UAIToken* Token = AITokenHolder->GetHeldToken())
		{
			return Token->GetTokenTag();
		}
	}

	return FGameplayTag();
}

bool UAITokenHolderComponent::IsHoldingToken() const
{
	return IsValid(AITokenHolder) && AITokenHolder->IsHoldingToken();
}
