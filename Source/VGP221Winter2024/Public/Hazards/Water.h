// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hazards/Hazard.h"
#include "Water.generated.h"

/**
 * 
 */
UCLASS()
class VGP221WINTER2024_API AWater : public AHazard
{
    GENERATED_BODY()

public:
    AWater();
    void EnterHazard(ACharacter* PlayerCharacter) override; 
    void ExitHazard(ACharacter* PlayerCharacter) override; 

private:
};
