// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AIControllerEnemy.h"

void AAIControllerEnemy::BeginPlay()
{
	Super::BeginPlay(); 

	RunBehaviorTree(behaviourTree);

	pawnSensing->OnSeePawn.AddDynamic(this, &AAIControllerEnemy::OnSeePawn);    
}

AAIControllerEnemy::AAIControllerEnemy()
{

	if (!pawnSensing) {
		pawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing")); 
	}
}

void AAIControllerEnemy::OnSeePawn(APawn* playerPawn)
{
	AFPSCharacter* player = Cast<AFPSCharacter>(playerPawn); 
	if (!player) return; 

	SetCanSeePlayer(true, player);  
}

void AAIControllerEnemy::SetCanSeePlayer(bool seePlayer, UObject* Player)
{
	UBlackboardComponent* bb = GetBlackboardComponent(); 
	bb->SetValueAsBool(FName("CanSeePlayer"), seePlayer); 

	if (seePlayer) {
		bb->SetValueAsObject(FName("PlayerTarget"), Player);  
	} 
}

void AAIControllerEnemy::RunTriggerableTimer() 
{  
	GetWorld()->GetTimerManager().ClearTimer(RetriggerableTimerHandle);  
	FunctionDelegate.BindUFunction(this, FName("SetCanSeePlayer"), false, GetPawn());  
	GetWorld()->GetTimerManager().SetTimer(RetriggerableTimerHandle, FunctionDelegate, pawnSensing->SensingInterval * 2.0f, false);    
}

