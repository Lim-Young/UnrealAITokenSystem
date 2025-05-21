// Copyright Lim Young.


#include "AITokenCoreEditor.h"

#define LOCTEXT_NAMESPACE "FAITokenCoreEditorModule"

void FAITokenCoreEditorModule::StartupModule()
{
	AITokenDataAssetTypeActions = MakeShared<FAITokenDataAssetTypeActions>();
	FAssetToolsModule::GetModule().Get().RegisterAssetTypeActions(AITokenDataAssetTypeActions.ToSharedRef());
}

void FAITokenCoreEditorModule::ShutdownModule()
{
	if (!FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		return;
	}

	FAssetToolsModule::GetModule().Get().UnregisterAssetTypeActions(AITokenDataAssetTypeActions.ToSharedRef());
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FAITokenCoreEditorModule, AITokenCoreEditor)
