#pragma once

#include "Modules/ModuleManager.h"

class FMyEditorFOVModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
    void AddToolbarExtension(class FToolBarBuilder& Builder);
};
