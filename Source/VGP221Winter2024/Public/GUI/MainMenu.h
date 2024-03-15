#pragma once

#include "CoreMinimal.h"
#include "GUI/ButtonWidget.h"
#include "Kismet/GameplayStatics.h" 
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "MainMenu.generated.h" 

UCLASS()
class VGP221WINTER2024_API UMainMenu : public UUserWidget 
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    UButtonWidget* StartButton; 

    UPROPERTY(meta = (BindWidget))
    UButtonWidget* ExitButton;

    UFUNCTION()
    void OnStartButtonClicked();

    UFUNCTION()
    void OnExitButtonClicked();
};  