// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h" 
#include "Hazard.generated.h"

UCLASS()
class VGP221WINTER2024_API AHazard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHazard();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* CollisionComponent; 

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	/*
	OverlappedComp: The component of the hazard that was overlapped. (THIS OBJECT) 
	OtherActor: The actor that overlapped with the hazard.
	OtherComp: The component of the other actor that overlapped with the hazard.
	OtherBodyIndex: Index of the body in the other actor that overlapped with the hazard.
	bFromSweep: Indicates whether the overlap was a result of a sweep.
	SweepResult: Additional information about the sweep result if bFromSweep is true.
	*/
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex); 
	virtual void EnterHazard(ACharacter* PlayerCharacter); 
	virtual void ExitHazard(ACharacter* PlayerCharacter); 

};
