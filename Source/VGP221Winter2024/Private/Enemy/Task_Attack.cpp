// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Task_Attack.h"

EBTNodeResult::Type UTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Attacking Player")));

	AFPSCharacter* PlayerCharacter = Cast<AFPSCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("PlayerTarget")));  
	if (!PlayerCharacter) return EBTNodeResult::Failed;

	float DamageAmount = 1.0f; 
	AAIController* AIOwner = Cast<AAIController>(OwnerComp.GetAIOwner());  
	if (!AIOwner) return EBTNodeResult::Failed; 
	PlayerCharacter->TakeDamage(DamageAmount,FDamageEvent(), AIOwner, AIOwner->GetPawn());;   
	
	return EBTNodeResult::Succeeded; 
}
