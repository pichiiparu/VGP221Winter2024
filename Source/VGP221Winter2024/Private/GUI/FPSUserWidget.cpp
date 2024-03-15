// Fill out your copyright notice in the Description page of Project Settings.


#include "GUI/FPSUserWidget.h"
#include "Kismet/GameplayStatics.h"  

void UFPSUserWidget::NativeConstruct()
{
	SetHealthBar(1.0f);
	SetScore(0);
	SetEmeraldScore(0); 

	/*if (ButtonWidgetPrefab) {
		for (int i = 0; i < 4; i++) 
		{
			UUserWidget* widget = CreateWidget(this, ButtonWidgetPrefab);
			ButtonContainer->AddChildToVerticalBox(widget);

			UButtonWidget* button = Cast<UButtonWidget>(widget); // Get Component in Unity
			button->SetText(i);
		}
	}*/
}

void UFPSUserWidget::SetHealthBar(float percentage)
{
	if (!HealthBar) return;

	HealthBar->SetPercent(percentage);
}

void UFPSUserWidget::SetScore(int newScore)
{
	if (!ScoreText) return;

	UIScore += newScore;
	ScoreText->SetText(FText::FromString("Rings: " + FString::FromInt(UIScore)));
}

void UFPSUserWidget::OpenLevelDelayed()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("Win")); 
}
 
void UFPSUserWidget::SetEmeraldScore(int newScore) 
{
	if (!EmeraldScoreText) return; 
	UIEmeraldScore += newScore;  
	EmeraldScoreText->SetText(FText::FromString("Chaos Emeralds: " + FString::FromInt(UIEmeraldScore)));  
	if (UIEmeraldScore >= 7) {
		FTimerHandle DelayTimerHandle;
		float DelaySeconds = 2.0f;
		FTimerDelegate TimerCallback;
		TimerCallback.BindUObject(this, &UFPSUserWidget::OpenLevelDelayed);
		GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, TimerCallback, DelaySeconds, false);
	} 
}
