// Copyright Lim Young.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"
#include "Condition/AITokenConditionPredicate.h"
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

	UPROPERTY(EditAnywhere, Category = "Token Config")
	float Cooldown = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Token Config")
	bool bUseRealTimeCooldown = false;

	UPROPERTY(EditAnywhere, Category = "Token Condition")
	TObjectPtr<UAITokenConditionPredicate> AITokenAcquireCondition;

	UPROPERTY(EditAnywhere, Category = "Token Condition")
	TObjectPtr<UAITokenConditionPredicate> AITokenPreemptCondition;

#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif
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

	UPROPERTY()
	TObjectPtr<UAITokenConditionPredicate> AcquireCondition;

	UPROPERTY()
	TObjectPtr<UAITokenConditionPredicate> PreemptCondition;

private:
	FGameplayTag TokenTag;

	EAITokenState TokenState = EAITokenState::Free;

	UPROPERTY()
	TObjectPtr<UAITokenHolder> Holder = nullptr;

	UPROPERTY()
	TObjectPtr<UAITokenSource> OwnerSource = nullptr;

	float Cooldown = 0.0f;
	bool bUseRealTimeCooldown = false;
	bool bOnCoolDown = false;
	float CooldownStart = 0.0f;

private:
	void InitToken(const UAITokenData* InTokenData, UAITokenSource* InOwnerSource);

	bool GrantedTo(UAITokenHolder* InHolder);
	bool LockToken();
	bool UnlockToken();
	// bool PreemptToken(UAITokenHolder* InHolder);
	bool Release();

	bool CheckAcquireCondition(const FAITokenConditionContext& Context);
	bool CheckPreemptCondition(const FAITokenConditionContext& Context) const;

public:
	FAITokenConditionContext GetSelfConditionContext() const;
	UAITokenSource* GetOwnerSource() const;
	UAITokenHolder* GetHolder() const;
	FGameplayTag GetTokenTag() const;

	bool HasHolder() const;
};

UCLASS()
class AITOKENCORE_API UAITokenContainer : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<UAITokenSource> OwnerSource = nullptr;

public:
	static UAITokenContainer* NewAITokenContainer(const UAITokenData* TokenData, int TokenCount, UObject* Outer);

	UPROPERTY()
	TArray<UAIToken*> Tokens;

	void InitAITokenContainer(const UAITokenData* TokenData, int TokenCount, UAITokenSource* Source);

	void ReleaseAllToken();

	bool TryGetCanAcquireToken(UAITokenHolder* Holder, UAIToken*& OutToken);

	bool TryGetAllCanPreemptTokens(UAITokenHolder* Holder, TArray<UAIToken*>& OutTokens);
};
