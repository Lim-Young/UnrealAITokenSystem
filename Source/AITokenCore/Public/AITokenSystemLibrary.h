// Copyright Lim Young.

#pragma once

#include "CoreMinimal.h"
#include "Component/AITokenHolderComponent.h"
#include "Component/AITokenSourceComponent.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AITokenSystemLibrary.generated.h"

/**
 * 
 */
UCLASS()
class AITOKENCORE_API UAITokenSystemLibrary : public UBlueprintFunctionLibrary
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

	UFUNCTION(BlueprintCallable, Category = "AITokenSystem", DisplayName = "Get AI Token Source Component")
	static bool GetAITokenSourceComponentFromActor(AActor* InActor, UAITokenSourceComponent*& OutSourceComponent);

	UFUNCTION(BlueprintCallable, Category = "AITokenSystem", DisplayName = "Get AI Token Holder Component")
	static bool GetAITokenHolderComponentFromActor(AActor* InActor, UAITokenHolderComponent*& OutHolderComponent);
};
