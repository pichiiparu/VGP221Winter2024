// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collectible/Collectible.h"
#include "Kismet/GameplayStatics.h"
#include "FPSGameMode.h"   
#include "Emerald.generated.h"

/**
 * 
 */
UCLASS()
class VGP221WINTER2024_API AEmerald : public ACollectible
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AEmerald();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnCollect() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* EmeraldMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Points = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RotationRate = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CollectRotationRate = 1500;

	FTimerHandle DeathTimerHandle;

	void DeathTimerComplete();
};
	