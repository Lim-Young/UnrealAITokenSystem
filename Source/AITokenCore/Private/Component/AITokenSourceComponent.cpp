// Copyright Lim Young.


#include "Component/AITokenSourceComponent.h"


// Sets default values for this component's properties
UAITokenSourceComponent::UAITokenSourceComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UAITokenSourceComponent::BeginPlay()
{
	InitAITokenSource();

	Super::BeginPlay();
}

void UAITokenSourceComponent::InitAITokenSource()
{
	if (!AITokenSource)
	{
		AITokenSource = NewObject<UAITokenSource>(this);
		check(AITokenSource);

		AITokenSource->InitTokenSource(AITokenSourceDefinition);
	}
}
