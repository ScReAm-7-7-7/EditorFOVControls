#include "MyEditorFOVCommands.h"

#define LOCTEXT_NAMESPACE "FMyEditorFOVCommands"

void FMyEditorFOVCommands::RegisterCommands()
{
    UI_COMMAND(IncreaseFOV,
               "Increase FOV",
               "Increase viewport FOV",
               EUserInterfaceActionType::Button,
               FInputChord(EKeys::Subtract, EModifierKey::Control));       // Ctrl + Numpad -

    UI_COMMAND(DecreaseFOV,
               "Decrease FOV",
               "Decrease viewport FOV",
               EUserInterfaceActionType::Button,
               FInputChord(EKeys::Add, EModifierKey::Control));  // Ctrl + Numpad +

    UI_COMMAND(ResetFOV,
               "Reset FOV",
               "Reset viewport FOV to default",
               EUserInterfaceActionType::Button,
               FInputChord(EKeys::Enter, EModifierKey::Control));     // Ctrl + Numpad Enter
}

#undef LOCTEXT_NAMESPACE
