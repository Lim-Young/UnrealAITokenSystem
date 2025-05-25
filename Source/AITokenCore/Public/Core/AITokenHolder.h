// Copyright Lim Young.

#pragma once

#include "CoreMinimal.h"
#include "AITokenSource.h"
#include "UObject/Object.h"
#include "AITokenHolder.generated.h"

UENUM(BlueprintType)
enum class EAITokenPreemptResultChooseType : uint8
{
	/**
	 * Choose the first preempt result that matches the condition.
	 */
	FirstMatch,
	/**
	 * Choose the preempt result with random selection.
	 */
	Random
};

USTRUCT(BlueprintType)
struct FAITokenHolderConfig
{
	GENERATED_BODY()

	/**
	 * If false, the token holder will not preempt the held token from other holders.
	 * And also, other holders cannot preempt the held token from this holder.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AITokenHolder|Preempt")
	bool bAllowPreempt = true;

	/**
	 * Control the priority of the token preemption mechanism;
	 * a holder with lower priority can never preempt the token from a holder with higher priority.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AITokenHolder|Preempt",
		meta = (EditCondition = "bAllowPreempt", EditConditionHides))
	uint8 Priority = 0;

	/**
	 * The method to choose the preempt result when multiple tokens match the preemption condition.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AITokenHolder|Preempt",
		meta = (EditCondition = "bAllowPreempt", EditConditionHides))
	EAITokenPreemptResultChooseType PreemptResultChooseType = EAITokenPreemptResultChooseType::Random;
};

/**
 * 
 */
UCLASS()
class AITOKENCORE_API UAITokenHolder : public UObject
{
	GENERATED_BODY()

	friend class UAIToken;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FAITokenHolderConfig TokenHolderConfig;

protected:
	UPROPERTY()
	TObjectPtr<UAIToken> HeldToken;

public:
	void InitTokenHolder(const FAITokenHolderConfig& InTokenHolderConfig);

public:
	UAIToken* GetHeldToken() const;
	bool IsHoldingToken() const;

public:
	bool AcquireTokenFromSource(UAITokenSource* Source, const FGameplayTag& TokenTag);
	bool ReleaseHeldToken();

	bool LockHeldToken() const;
	bool UnlockHeldToken() const;
};
