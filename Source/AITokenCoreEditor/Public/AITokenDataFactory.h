// Copyright Lim Young.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "AITokenDataFactory.generated.h"

/**
 * 
 */
UCLASS()
class AITOKENCOREEDITOR_API UAITokenDataFactory : public UFactory
{
	GENERATED_BODY()

public:
	UAITokenDataFactory();

	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
		UObject* Context, FFeedbackContext* Warn) override;
};
