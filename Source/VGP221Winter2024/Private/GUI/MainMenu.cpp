// MainMenu.cpp

#include "GUI/MainMenu.h"
 
void UMainMenu::NativeConstruct()
{
    Super::NativeConstruct();

    if (StartButton)
    {
        StartButton->SetText(FText::FromString("Start"));
        StartButton->Button->OnClicked.AddDynamic(this, &UMainMenu::OnStartButtonClicked);
    }

    if (ExitButton)
    {
        ExitButton->SetText(FText::FromString("Exit"));
        ExitButton->Button->OnClicked.AddDynamic(this, &UMainMenu::OnExitButtonClicked);
    }
}

void UMainMenu::OnStartButtonClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("Start button clicked"));
    UGameplayStatics::OpenLevel(GetWorld(), FName("FPSMap"));
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0); 
    PlayerController->bShowMouseCursor = false; 
}

void UMainMenu::OnExitButtonClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("Exit button clicked"));
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        PlayerController->ConsoleCommand("quit");
    }
}
