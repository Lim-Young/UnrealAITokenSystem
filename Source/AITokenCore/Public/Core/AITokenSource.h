// Copyright Lim Young.

#pragma once

#include "CoreMinimal.h"
#include "AIToken.h"
#include "UObject/Object.h"
#include "AITokenSource.generated.h"

USTRUCT(BlueprintType)
struct FAITokenSourceDefinition
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "AITokenSource", meta = (ClampMin = 1))
	TMap<TObjectPtr<UAITokenData>, int> SourceTokens;
};

/**
 * 
 */
UCLASS()
class AITOKENCORE_API UAITokenSource : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	TMap<FGameplayTag, TObjectPtr<UAITokenContainer>> Tokens;

	UPROPERTY()
	TMap<FGameplayTag, TObjectPtr<UAIToken>> PreemptTestTokens;

	UAITokenSource() = default;

	void AddOrResetToken(UAITokenData* TokenData, const int TokenCount = 1);
	void CreatePreemptTestToken(const TObjectPtr<UAITokenData>& TokenData);

public:
	void InitTokenSource(const FAITokenSourceDefinition& TokenSourceDefinition);

	UAIToken* TakeToken(const FGameplayTag& TokenTag, UAITokenHolder* Holder);
};
