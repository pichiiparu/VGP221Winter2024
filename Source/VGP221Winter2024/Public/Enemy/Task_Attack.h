// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Engine/DamageEvents.h"
#include "Enemy/AIControllerEnemy.h" 
#include "Player/FPSCharacter.h"
#include "Task_Attack.generated.h"

/**
 * 
 */
UCLASS()
class VGP221WINTER2024_API UTask_Attack : public UBTTaskNode
{
	GENERATED_BODY()
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override; 
	
};
