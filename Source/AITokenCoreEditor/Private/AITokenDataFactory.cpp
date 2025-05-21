// Copyright Lim Young.


#include "AITokenDataFactory.h"

#include "Core/AIToken.h"

UAITokenDataFactory::UAITokenDataFactory()
{
	SupportedClass = UAITokenData::StaticClass();
	bCreateNew = true;
}

UObject* UAITokenDataFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
                                                UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UAITokenData>(InParent, InClass, InName, Flags, Context);
}
