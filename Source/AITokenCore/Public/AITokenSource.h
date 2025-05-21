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

	UPROPERTY(EditAnywhere, Category = "AITokenSource")
	TMap<TObjectPtr<UAITokenAsset>, int> SourceTokens;
};

/**
 * 
 */
UCLASS()
class AITOKENCORE_API UAITokenSource : public UObject
{
	GENERATED_BODY()

	TMap<FGameplayTag, TObjectPtr<UAITokenContainer>> Tokens;

private:
	void AddOrResetToken(const FGameplayTag& TokenTag, const int TokenCount = 1);

public:
	void InitTokenSource(const FAITokenSourceDefinition& TokenSourceDefinition);
	bool TakeToken(UAITokenHolder* TokenHolder, const FGameplayTag& TokenTag);
	bool ReturnToken(UAITokenHolder* TokenHolder, const FGameplayTag& TokenTag, const int TokenCount = 1);
};
