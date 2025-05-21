// Copyright Lim Young.


#include "AITokenDataAssetTypeActions.h"

#include "Core/AIToken.h"


UClass* FAITokenDataAssetTypeActions::GetSupportedClass() const
{
	return UAITokenData::StaticClass();
}

FText FAITokenDataAssetTypeActions::GetName() const
{
	return INVTEXT("AI Token Data");
}

FColor FAITokenDataAssetTypeActions::GetTypeColor() const
{
	return FColor(0, 173, 181);
}

uint32 FAITokenDataAssetTypeActions::GetCategories()
{
	return FAssetToolsModule::GetModule().Get().RegisterAdvancedAssetCategory(
		FName(TEXT("AITokenSystem")), INVTEXT("AI Token System"));
}
