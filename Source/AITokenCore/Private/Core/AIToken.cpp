// Copyright Lim Young.


#include "Core/AIToken.h"

#include "Core/AITokenHolder.h"
#include "Core/AITokenSource.h"
#include "Kismet/GameplayStatics.h"
#if WITH_EDITOR
#include "Misc/DataValidation.h"
#endif

DEFINE_LOG_CATEGORY(LogAITokenSystem);

UE_DEFINE_GAMEPLAY_TAG_COMMENT(AIToken, "AIToken", "AI token root tag");

#if WITH_EDITOR
EDataValidationResult UAITokenData::IsDataValid(FDataValidationContext& Context) const
{
	if (Super::IsDataValid(Context) == EDataValidationResult::Invalid)
	{
		return EDataValidationResult::Invalid;
	}

	if (!TokenTag.IsValid())
	{
		Context.AddError(
			NSLOCTEXT("AIToken", "TokenTagInvalid",
			          "TokenTag is Empty or Invalid. Please set a valid GameplayTag for the token."));
		return EDataValidationResult::Invalid;
	}

	if (!TokenTag.MatchesTag(AIToken))
	{
		Context.AddError(
			FText::Format(
				NSLOCTEXT("AIToken", "TokenTagNotMatch", "TokenTag {0} does not match \"AIToken\" root tag."),
				FText::FromName(TokenTag.GetTagName())
			)
		);
		return EDataValidationResult::Invalid;
	}

	return EDataValidationResult::Valid;
}
#endif

void UAIToken::InitToken(const UAITokenData* InTokenData, UAITokenSource* InOwnerSource)
{
	TokenState = EAITokenState::Free;
	TokenTag = InTokenData->TokenTag;
	Cooldown = InTokenData->Cooldown;
	bUseRealTimeCooldown = InTokenData->bUseRealTimeCooldown;
	OwnerSource = InOwnerSource;

	AcquireCondition = DuplicateObject<UAITokenConditionPredicate>(InTokenData->AITokenAcquireCondition, this);
	PreemptCondition = DuplicateObject<UAITokenConditionPredicate>(InTokenData->AITokenPreemptCondition, this);
}

bool UAIToken::GrantedTo(UAITokenHolder* InHolder)
{
	if (TokenState == EAITokenState::Free)
	{
		TokenState = EAITokenState::Held;
		Holder = InHolder;
		return true;
	}
	return false;
}

bool UAIToken::LockToken()
{
	if (!HasHolder())
	{
		UE_LOG(LogAITokenSystem, Verbose, TEXT("LockToken failed: Token has no holder"));
		return false;
	}

	if (TokenState == EAITokenState::Locked)
	{
		UE_LOG(LogAITokenSystem, Verbose, TEXT("Token is already locked"));
		return true;
	}

	if (TokenState == EAITokenState::Held)
	{
		TokenState = EAITokenState::Locked;
		return true;
	}

	return false;
}

bool UAIToken::UnlockToken()
{
	if (TokenState == EAITokenState::Locked)
	{
		// Because the token is locked, so we can sure that the token has a holder
		check(HasHolder())

		TokenState = EAITokenState::Held;
		return true;
	}

	UE_LOG(LogAITokenSystem, Verbose, TEXT("UnlockToken failed: Token is not locked"));
	return false;
}

// bool UAIToken::PreemptToken(UAITokenHolder* InHolder)
// {
// 	// if (TokenState == EAITokenState::Held && Holder == InHolder)
// 	// {
// 	// 	TokenState = EAITokenState::Free;
// 	// 	Holder = nullptr;
// 	// 	return true;
// 	// }
// 	// return false;
// 	return true;
// }

bool UAIToken::Release()
{
	if (TokenState == EAITokenState::Locked)
	{
		UE_LOG(LogAITokenSystem, Verbose, TEXT("Token is locked, cannot release"));
		return false;
	}

	if (TokenState == EAITokenState::Held)
	{
		TokenState = EAITokenState::Free;
		Holder = nullptr;

		if (Cooldown > 0.0f)
		{
			bOnCoolDown = true;
			if (bUseRealTimeCooldown)
			{
				CooldownStart = UGameplayStatics::GetRealTimeSeconds(OwnerSource);
			}
			else
			{
				CooldownStart = UGameplayStatics::GetTimeSeconds(OwnerSource);
			}
		}

		return true;
	}

	UE_LOG(LogAITokenSystem, Verbose, TEXT("Token is not held, cannot release"));
	return false;
}

bool UAIToken::CheckAcquireCondition(const FAITokenConditionContext& Context)
{
	if (!IsValid(AcquireCondition))
	{
		return true;
	}

	if (bOnCoolDown)
	{
		float CurrentTime;
		if (bUseRealTimeCooldown)
		{
			CurrentTime = UGameplayStatics::GetRealTimeSeconds(OwnerSource);
		}
		else
		{
			CurrentTime = UGameplayStatics::GetTimeSeconds(OwnerSource);
		}

		if (CurrentTime - CooldownStart > Cooldown)
		{
			bOnCoolDown = false;
		}
		else
		{
			return false;
		}
	}

	return AcquireCondition->Evaluate(Context);
}

bool UAIToken::CheckPreemptCondition(const FAITokenConditionContext& Context) const
{
	if (!IsValid(Holder) || !Context.HasTokenHolder())
	{
		checkNoEntry();
		return false;
	}

	if (Holder->TokenHolderConfig.Priority > Context.TokenHolder->TokenHolderConfig.Priority)
	{
		return false;
	}

	if (!IsValid(PreemptCondition))
	{
		return true;
	}

	return PreemptCondition->Evaluate(Context);
}

FAITokenConditionContext UAIToken::GetSelfConditionContext() const
{
	return FAITokenConditionContext(OwnerSource, Holder);
}

UAITokenSource* UAIToken::GetOwnerSource() const
{
	return OwnerSource;
}

UAITokenHolder* UAIToken::GetHolder() const
{
	return Holder;
}

FGameplayTag UAIToken::GetTokenTag() const
{
	return TokenTag;
}

bool UAIToken::HasHolder() const
{
	return IsValid(Holder.Get());
}

UAITokenContainer* UAITokenContainer::NewAITokenContainer(const UAITokenData* TokenData, const int TokenCount,
                                                          UObject* Outer)
{
	UAITokenContainer* TokenContainer = NewObject<UAITokenContainer>(Outer);
	if (TokenContainer)
	{
		TokenContainer->InitAITokenContainer(TokenData, TokenCount, CastChecked<UAITokenSource>(Outer));
	}
	return TokenContainer;
}

void UAITokenContainer::InitAITokenContainer(const UAITokenData* TokenData, const int TokenCount,
                                             UAITokenSource* Source)
{
	OwnerSource = Source;

	Tokens.Empty(TokenCount);
	for (int i = 0; i < TokenCount; i++)
	{
		UAIToken* Token = NewObject<UAIToken>(Source);
		Token->InitToken(TokenData, Source);
		Tokens.Add(Token);
	}
}

void UAITokenContainer::ReleaseAllToken()
{
	if (Tokens.Num() == 0)
	{
		return;
	}

	for (const UAIToken* Token : Tokens)
	{
		if (!IsValid(Token))
		{
			continue;
		}

		if (!Token->HasHolder())
		{
			continue;
		}

		if (Token->TokenState == EAITokenState::Locked)
		{
			if (!Token->GetHolder()->UnlockHeldToken())
			{
				continue;
			}
		}

		Token->GetHolder()->ReleaseHeldToken();
	}
}

bool UAITokenContainer::TryGetCanAcquireToken(UAITokenHolder* Holder, UAIToken*& OutToken)
{
	const FAITokenConditionContext Context(OwnerSource, Holder);
	for (UAIToken* Token : Tokens)
	{
		if (IsValid(Token) && Token->TokenState == EAITokenState::Free)
		{
			if (Token->CheckAcquireCondition(Context))
			{
				OutToken = Token;
				return true;
			}
		}
	}
	return false;
}

bool UAITokenContainer::TryGetAllCanPreemptTokens(UAITokenHolder* Holder, TArray<UAIToken*>& OutTokens)
{
	TArray<UAIToken*> HeldTokens;

	for (UAIToken* Token : Tokens)
	{
		if (IsValid(Token) && Token->TokenState == EAITokenState::Held)
		{
			if (!Token->GetHolder()->TokenHolderConfig.bAllowPreempt)
			{
				continue;
			}

			// If the token current holder cannot preempt, that is we need.
			if (Token->CheckPreemptCondition(Token->GetSelfConditionContext()))
			{
				continue;
			}

			HeldTokens.Add(Token);
		}
	}

	if (HeldTokens.Num() > 0)
	{
		OutTokens = HeldTokens;
		return true;
	}

	return false;
}
