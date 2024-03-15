// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectible/Emerald.h"

AEmerald::AEmerald()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!EmeraldMeshComponent)
	{
		EmeraldMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EmeraldMeshComponent"));
		EmeraldMeshComponent->SetupAttachment(RootComponent);
	}
}

// Called when the game starts or when spawned
void AEmerald::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEmerald::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalRotation(FRotator(0, RotationRate * DeltaTime, 0));

}

void AEmerald::OnCollect()
{
	Super::OnCollect();  
	RotationRate = CollectRotationRate;
	GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &AEmerald::DeathTimerComplete, 0.5f, false);
}

void AEmerald::DeathTimerComplete()
{
	AFPSGameMode* Gamemode = Cast<AFPSGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (Gamemode) {
		Gamemode->CurrentWidget->SetEmeraldScore(Points); 
	}
	Destroy(); 
}
