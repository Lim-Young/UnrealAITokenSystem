// Copyright Lim Young.

#pragma once

#include "CoreMinimal.h"
#include "AITokenDataAssetTypeActions.h"
#include "Modules/ModuleManager.h"

class FAITokenCoreEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
    TSharedPtr<FAITokenDataAssetTypeActions> AITokenDataAssetTypeActions;
};
