#pragma once

#include "CoreMinimal.h"
#include "GUI/ButtonWidget.h"
#include "Kismet/GameplayStatics.h"  
#include "Blueprint/UserWidget.h" 
#include "Components/VerticalBox.h" 
#include "Components/Button.h" 
#include "WinGame.generated.h"   
 
UCLASS()
class VGP221WINTER2024_API UWinGame : public UUserWidget  
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    UButtonWidget* MainMenuButton; 

    UPROPERTY(meta = (BindWidget))
    UButtonWidget* ExitButton;

    UFUNCTION()
    void OnMainMenuButtonClicked();

    UFUNCTION()
    void OnExitButtonClicked();
};