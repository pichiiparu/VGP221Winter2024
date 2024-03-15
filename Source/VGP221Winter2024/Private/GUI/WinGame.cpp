// MainMenu.cpp

#include "GUI/WinGame.h"

void UWinGame::NativeConstruct()
{
    Super::NativeConstruct(); 

    if (MainMenuButton)
    {
        MainMenuButton->SetText(FText::FromString("Return to Menu"));
        MainMenuButton->Button->OnClicked.AddDynamic(this, &UWinGame::OnMainMenuButtonClicked);
    }

    if (ExitButton)
    {
        ExitButton->SetText(FText::FromString("Exit"));
        ExitButton->Button->OnClicked.AddDynamic(this, &UWinGame::OnExitButtonClicked);
    }
} 

void UWinGame::OnMainMenuButtonClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("Start button clicked"));
    UGameplayStatics::OpenLevel(GetWorld(), FName("Menu"));
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    PlayerController->bShowMouseCursor = false;
}

void UWinGame::OnExitButtonClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("Exit button clicked"));
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        PlayerController->ConsoleCommand("quit");
    }
} 
