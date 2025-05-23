// Copyright Lim Young.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"
#include "Condition/AITokenConditionPredicate.h"
#include "StructUtils/InstancedStruct.h"
#include "UObject/Object.h"
#include "AIToken.generated.h"

class UAITokenHolder;
DECLARE_LOG_CATEGORY_EXTERN(LogAITokenSystem, Log, All);

UE_DECLARE_GAMEPLAY_TAG_EXTERN(AIToken);

UENUM()
enum class EAITokenState
{
	Free,
	Held,
	Locked
};

UCLASS(BlueprintType)
class AITOKENCORE_API UAITokenData : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Token Config", meta = (Categories = AIToken))
	FGameplayTag TokenTag;

	UPROPERTY(EditAnywhere, Category = "Token Condition",
		meta = (BaseStruct = "/Script/AITokenCore.AITokenConditionPredicate", ExcludeBasestruct))
	FInstancedStruct AITokenAcquireCondition;
};

/**
 * The UAIToken Outer is the UAITokenSource
 */
UCLASS()
class AITOKENCORE_API UAIToken : public UObject
{
	GENERATED_BODY()

	friend class UAITokenSource;
	friend class UAITokenHolder;
	friend class UAITokenContainer;

	FAITokenConditionPredicate AcquireCondition;

public:
	FGameplayTag TokenTag;

	EAITokenState TokenState = EAITokenState::Free;

	UPROPERTY()
	TObjectPtr<UAITokenHolder> Holder = nullptr;

	UPROPERTY()
	TObjectPtr<UAITokenSource> OwnerSource = nullptr;

private:
	void InitToken(const FGameplayTag InTokenTag, UAITokenSource* InOwnerSource);

	bool GrantedTo(UAITokenHolder* InHolder);

	bool LockToken();
	bool UnlockToken();
	// bool PreemptToken(UAITokenHolder* InHolder);

	bool Release();

public:
	UAITokenSource* GetOwnerSource() const;
	UAITokenHolder* GetHolder() const;

	bool HasHolder() const;
};

UCLASS()
class AITOKENCORE_API UAITokenContainer : public UObject
{
	GENERATED_BODY()

public:
	static UAITokenContainer* NewAITokenContainer(const FGameplayTag TokenTag, const int TokenCount, UObject* Outer);

	UPROPERTY()
	TArray<UAIToken*> Tokens;

	void InitAITokenContainer(FGameplayTag TokenTag, int TokenCount, UAITokenSource* Source);

	void ReleaseAllToken();

	bool TryGetFreeToken(UAIToken*& OutToken);

	bool TryGetAllHeldToken(TArray<UAIToken*>& OutTokens);
};
