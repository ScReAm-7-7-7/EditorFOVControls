#include "MyEditorFOVModule.h"
#include "MyEditorFOVCommands.h"
#include "LevelEditor.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "EditorViewportClient.h"
#include "Editor.h"
#include "Framework/Commands/UICommandList.h"

#define LOCTEXT_NAMESPACE "FMyEditorFOVModule"

TSharedPtr<FUICommandList> PluginCommands;

// --- Helpers to get active viewport ---
static FEditorViewportClient* GetActiveViewportClient()
{
    for (FEditorViewportClient* Client : GEditor->GetAllViewportClients())
    {
        if (Client && Client->IsPerspective() && Client->Viewport && Client->Viewport->IsForegroundWindow())
        {
            return Client;
        }
    }
    return nullptr;
}

// --- FOV adjustment functions ---
static void AdjustFOV(float Delta)
{
    if (FEditorViewportClient* ViewportClient = GetActiveViewportClient())
    {
        float NewFOV = ViewportClient->ViewFOV + Delta;
        ViewportClient->ViewFOV = NewFOV;

        ViewportClient->Invalidate(true, true);
        if (ViewportClient->Viewport)
        {
            ViewportClient->Viewport->Draw();
        }
    }
}

static void SetFOV(float NewFOV)
{
    if (FEditorViewportClient* ViewportClient = GetActiveViewportClient())
    {
        ViewportClient->ViewFOV = NewFOV;

        ViewportClient->Invalidate(true, true);
        if (ViewportClient->Viewport)
        {
            ViewportClient->Viewport->Draw();
        }
    }
}

// --- Command handlers ---
static void HandleIncreaseFOV() { AdjustFOV(+5.0f); }
static void HandleDecreaseFOV() { AdjustFOV(-5.0f); }
static void HandleResetFOV() { SetFOV(90.0f); }


    

// --- Module implementation ---
void FMyEditorFOVModule::StartupModule()
{
    FMyEditorFOVCommands::Register();

    PluginCommands = MakeShareable(new FUICommandList);

    PluginCommands->MapAction(
        FMyEditorFOVCommands::Get().IncreaseFOV,
        FExecuteAction::CreateStatic(&HandleIncreaseFOV),
        FCanExecuteAction()
    );

    PluginCommands->MapAction(
        FMyEditorFOVCommands::Get().DecreaseFOV,
        FExecuteAction::CreateStatic(&HandleDecreaseFOV),
        FCanExecuteAction()
    );

    PluginCommands->MapAction(
        FMyEditorFOVCommands::Get().ResetFOV,
        FExecuteAction::CreateStatic(&HandleResetFOV),
        FCanExecuteAction()
    );

    if (FModuleManager::Get().IsModuleLoaded("LevelEditor"))
    {
        FLevelEditorModule& LevelEditorModule =
            FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

        LevelEditorModule.GetGlobalLevelEditorActions()->Append(PluginCommands.ToSharedRef());

        TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
        ToolbarExtender->AddToolBarExtension(
            "Play",
            EExtensionHook::After,
            PluginCommands,
            FToolBarExtensionDelegate::CreateRaw(this, &FMyEditorFOVModule::AddToolbarExtension)
        );

        LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
    }
}

void FMyEditorFOVModule::ShutdownModule()
{
    FMyEditorFOVCommands::Unregister();
}

void FMyEditorFOVModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
    Builder.AddComboButton(
        FUIAction(),
        FOnGetContent::CreateLambda([this]() -> TSharedRef<SWidget>
        {
            FMenuBuilder MenuBuilder(true, PluginCommands);
            MenuBuilder.AddMenuEntry(FMyEditorFOVCommands::Get().IncreaseFOV);
            MenuBuilder.AddMenuEntry(FMyEditorFOVCommands::Get().DecreaseFOV);
            MenuBuilder.AddMenuEntry(FMyEditorFOVCommands::Get().ResetFOV);
            return MenuBuilder.MakeWidget();
        }),
        LOCTEXT("FOVControls_Label", "FOV Controls"),
        LOCTEXT("FOVControls_Tooltip", "Adjust viewport FOV"),
        FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.ViewOptions")
    );
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FMyEditorFOVModule, MyEditorFOV)
