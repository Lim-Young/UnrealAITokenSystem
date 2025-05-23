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

		AITokenHolder->InitTokenHolder(Priority);
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
			return Token->TokenTag;
		}
	}

	return FGameplayTag();
}
