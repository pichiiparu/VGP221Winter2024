// Fill out your copyright notice in the Description page of Project Settings.

#include "Hazards/Water.h"
#include "Player/FPSCharacter.h"  

AWater::AWater()
{
}


void AWater::EnterHazard(ACharacter* PlayerCharacter)
{
    Super::EnterHazard(PlayerCharacter);
    ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    AFPSCharacter* FPSPlayerCharacter = Cast<AFPSCharacter>(player);
    FPSPlayerCharacter->ApplyWaterPostProcessMaterial(true);
}

void AWater::ExitHazard(ACharacter* PlayerCharacter)
{
    Super::ExitHazard(PlayerCharacter);

    ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    AFPSCharacter* FPSPlayerCharacter = Cast<AFPSCharacter>(player);
    FPSPlayerCharacter->ApplyWaterPostProcessMaterial(false);
}
