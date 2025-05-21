// Copyright Lim Young.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AITokenHolder.generated.h"

/**
 * 
 */
UCLASS()
class AITOKENCORE_API UAITokenHolder : public UObject
{
	GENERATED_BODY()

	friend class UAIToken;

public:
	/**
	 * 
	 */
	uint8 Priority = 0;

protected:
	UPROPERTY()
	TObjectPtr<UAIToken> HeldToken;

public:
	void InitTokenHolder(const uint8 InPriority);

private:
	// Only Use for AIToken
	void HoldToken(UAIToken* InToken);
	void ReleaseToken();
	// End

public:
	UAIToken* GetHeldToken() const;
	bool IsHoldingToken() const;
};
