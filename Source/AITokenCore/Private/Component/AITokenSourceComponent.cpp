// Copyright Lim Young.


#include "Component/AITokenSourceComponent.h"

#if WITH_EDITOR
#include "Misc/DataValidation.h"
#endif


// Sets default values for this component's properties
UAITokenSourceComponent::UAITokenSourceComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

#if WITH_EDITOR
EDataValidationResult UAITokenSourceComponent::IsDataValid(FDataValidationContext& Context) const
{
	if (Super::IsDataValid(Context) == EDataValidationResult::Invalid)
	{
		return EDataValidationResult::Invalid;
	}

	TMap<FGameplayTag, TObjectPtr<UAITokenData>> TokenDataMap;
	for (const auto TokenData : AITokenSourceDefinition.SourceTokens)
	{
		if (!IsValid(TokenData.Key))
		{
			// Has Empty Key
			Context.AddError(NSLOCTEXT("AIToken", "TokenDataKeyInvalid",
			                           "SourceTokens Map has Empty Key. Please set a valid AITokenData asset as the key."));
			return EDataValidationResult::Invalid;
		}

		// Because we have AITokenData validation, we can safely assume that TokenData is valid.
		// TODO: Maybe we can remove this in future.
		if (!TokenData.Key->TokenTag.IsValid())
		{
			Context.AddWarning(NSLOCTEXT("AIToken", "TokenTagInvalid",
			                             "TokenTag is Empty or Invalid. Please set a valid GameplayTag for the token."));
		}

		if (TokenDataMap.Contains(TokenData.Key->TokenTag))
		{
			Context.AddError(
				FText::Format(
					NSLOCTEXT("AIToken", "TokenTagDuplicate",
					          "TokenTag {0} is duplicated in the AITokenSourceDefinition. Please remove the duplicate."),
					FText::FromName(TokenData.Key->TokenTag.GetTagName()
					)
				)
			);
			Context.AddError(
				FText::Format(
					NSLOCTEXT("AIToken", "TokenTagDuplicateData",
					          "Duplicate token data is {0} and {1}. Please check the AITokenData asset."),
					FText::FromName(TokenDataMap[TokenData.Key->TokenTag]->GetFName()),
					FText::FromName(TokenData.Key->GetFName()
					)
				)
			);
			return EDataValidationResult::Invalid;
		}
		TokenDataMap.Add(TokenData.Key->TokenTag, TokenData.Key);
	}
	TokenDataMap.Empty();

	bool bValid = true;
	for (const auto TokenData : AITokenSourceDefinition.SourceTokens)
	{
		if (TokenData.Value <= 0)
		{
			Context.AddError(
				FText::Format(
					NSLOCTEXT("AIToken", "TokenCountInvalid",
					          "Token count {0} is invalid. Please set a valid token count greater than 0."),
					FText::AsNumber(TokenData.Value)
				)
			);
			bValid = false;
		}
	}
	if (!bValid)
	{
		return EDataValidationResult::Invalid;
	}

	return EDataValidationResult::Valid;
}
#endif

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

UAITokenSource* UAITokenSourceComponent::GetAITokenSource() const
{
	return AITokenSource;
}
