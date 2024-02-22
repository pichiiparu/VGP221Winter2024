// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h" 
#include "Perception/PawnSensingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h" 
#include "Player/FPSCharacter.h" 
#include "GameFramework/DamageType.h" 
#include "AIControllerEnemy.generated.h"

/**
 * 
 */
UCLASS()
class VGP221WINTER2024_API AAIControllerEnemy : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	AAIControllerEnemy(); 

	UPROPERTY(EditAnywhere)
	UPawnSensingComponent* pawnSensing; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBehaviorTree* behaviourTree;            

	UFUNCTION()
	void OnSeePawn(APawn* playerPawn); 

	UFUNCTION()
	void SetCanSeePlayer(bool seePlayer, UObject* Player); 

	FTimerHandle RetriggerableTimerHandle;  
	FTimerDelegate FunctionDelegate;   
	void RunTriggerableTimer(); 
}; 
