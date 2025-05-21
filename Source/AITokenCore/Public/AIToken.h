// Copyright Lim Young.

#pragma once

#include "CoreMinimal.h"
#include "AITokenHolder.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"
#include "UObject/Object.h"
#include "AIToken.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(AIToken);

UENUM()
enum class EAITokenState
{
	Free,
	Held,
	Locked
};

UCLASS()
class UAITokenAsset : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Token Config")
	FGameplayTag TokenTag;
};

/**
 * 
 */
UCLASS()
class AITOKENCORE_API UAIToken : public UObject
{
	GENERATED_BODY()

public:
	FGameplayTag TokenTag;

	EAITokenState TokenState = EAITokenState::Free;

	UPROPERTY()
	TObjectPtr<UAITokenHolder> Holder = nullptr;

	bool AcquireToken(UAITokenHolder* InHolder);

	bool LockToken(UAITokenHolder* InHolder);

	bool PreemptToken(UAITokenHolder* InHolder);

	bool ReleaseToken();
};

UCLASS()
class UAITokenContainer : public UObject
{
	GENERATED_BODY()

public:
	static UAITokenContainer* NewAITokenContainer(const FGameplayTag TokenTag, const int TokenCount, UObject* Outer);

	UPROPERTY()
	TArray<UAIToken*> Tokens;

	void InitAITokenContainer(const FGameplayTag TokenTag, const int TokenCount);

	void ReleaseAllToken();

	bool TryGetFreeToken(UAIToken*& OutToken);
};
