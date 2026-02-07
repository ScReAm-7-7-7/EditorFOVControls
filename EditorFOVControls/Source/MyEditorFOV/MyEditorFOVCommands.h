#pragma once

#include "Framework/Commands/Commands.h"
#include "Styling/AppStyle.h"

class FMyEditorFOVCommands : public TCommands<FMyEditorFOVCommands>
{
public:
    FMyEditorFOVCommands()
        : TCommands<FMyEditorFOVCommands>(
            TEXT("MyEditorFOV"),
            NSLOCTEXT("Contexts", "MyEditorFOV", "Editor FOV Controls"),
            NAME_None,
            FAppStyle::GetAppStyleSetName()   // ✅ correct for UE5
        )
    {
    }

    virtual void RegisterCommands() override;

public:
    TSharedPtr<FUICommandInfo> IncreaseFOV;
    TSharedPtr<FUICommandInfo> DecreaseFOV;
    TSharedPtr<FUICommandInfo> ResetFOV;
};
