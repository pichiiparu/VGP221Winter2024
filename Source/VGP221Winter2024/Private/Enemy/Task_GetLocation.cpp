// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Task_GetLocation.h"

EBTNodeResult::Type UTask_GetLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>((UGameplayStatics::GetPlayerPawn(GetWorld(), 0))); 
	// 1 Try to get random point on navmesh 
	// 2 If successful set the random patrol location to that value
	// 3 if failed return failed 

	if (NavArea) {
		NavArea->K2_GetRandomLocationInNavigableRadius(GetWorld(), GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(),RandomLocation,2000.0f);  
	}
	else {
		return EBTNodeResult::Failed;
	}
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("RandomPatrolLocation"), RandomLocation); 

	return EBTNodeResult::Succeeded; 
}
