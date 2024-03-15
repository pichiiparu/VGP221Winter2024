// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GUI/ButtonWidget.h"
#include "Kismet/GameplayStatics.h"  
#include "Blueprint/UserWidget.h" 
#include "Components/VerticalBox.h" 
#include "Components/Button.h"  
#include "GameOver.generated.h" 

/**
 * 
 */
UCLASS()
class VGP221WINTER2024_API UGameOver : public UUserWidget
{
    GENERATED_BODY()   
     
public:
    virtual void NativeConstruct() override; 

    UPROPERTY(meta = (BindWidget))
    UButtonWidget* RetryButton;

    UPROPERTY(meta = (BindWidget))
    UButtonWidget* ExitButton;

    UFUNCTION()
    void OnRetryButtonClicked();  

    UFUNCTION()
    void OnExitButtonClicked(); 
};
