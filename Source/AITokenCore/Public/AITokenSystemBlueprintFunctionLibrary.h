// Copyright Blazebone Game Studio

#pragma once

#include "CoreMinimal.h"
#include "Component/AITokenHolderComponent.h"
#include "Component/AITokenSourceComponent.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AITokenSystemBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class AITOKENCORE_API UAITokenSystemBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "AITokenSystem", DisplayName = "Acquire AI Token From Source",
		meta = (GameplayTagFilter = AIToken))
	static bool AcquireAITokenFromSourceComponent(UAITokenHolderComponent* HolderComponent,
	                                              UAITokenSourceComponent* SourceComponent,
	                                              FGameplayTag TokenTag);

	static bool AcquireAITokenFromSource(UAITokenHolder* Holder, UAITokenSource* Source, FGameplayTag TokenTag);

	UFUNCTION(BlueprintCallable, Category = "AITokenSystem", DisplayName = "Release AI Token To Source",
		meta = (GameplayTagFilter = AIToken))
	static bool ReleaseAITokenToSourceComponent(UAITokenHolderComponent* HolderComponent);

	static bool ReleaseAITokenToSource(UAITokenHolder* Holder);

	UFUNCTION(BlueprintCallable, Category = "AITokenSystem", DisplayName = "Lock Held Token",
		meta = (GameplayTagFilter = AIToken))
	static bool LockHeldToken(UAITokenHolderComponent* HolderComponent);

	UFUNCTION(BlueprintCallable, Category = "AITokenSystem", DisplayName = "Unlock Held Token",
		meta = (GameplayTagFilter = AIToken))
	static bool UnlockHeldToken(UAITokenHolderComponent* HolderComponent);
};
