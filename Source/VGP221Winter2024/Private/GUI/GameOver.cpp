// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/GameOver.h"

void UGameOver::NativeConstruct()
{
    Super::NativeConstruct();   

    if (RetryButton) 
    {
        RetryButton->SetText(FText::FromString("Retry")); 
        RetryButton->Button->OnClicked.AddDynamic(this, &UGameOver::OnRetryButtonClicked);    
    }

    if (ExitButton)
    {
        ExitButton->SetText(FText::FromString("Exit"));
        ExitButton->Button->OnClicked.AddDynamic(this, &UGameOver::OnExitButtonClicked); 
    } 
}

void UGameOver::OnRetryButtonClicked()  
{
    UE_LOG(LogTemp, Warning, TEXT("Start button clicked"));
    UGameplayStatics::OpenLevel(GetWorld(), FName("FPSMap"));
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    PlayerController->bShowMouseCursor = false;
}

void UGameOver::OnExitButtonClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("Exit button clicked"));
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        PlayerController->ConsoleCommand("quit");
    }
}
