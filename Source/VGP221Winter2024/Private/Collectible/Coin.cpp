// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectible/Coin.h"

ACoin::ACoin()
{ 
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!CoinMeshComponent)
	{
		CoinMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoinMeshComponent"));
		CoinMeshComponent->SetupAttachment(RootComponent);
	} 
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalRotation(FRotator(0, RotationRate * DeltaTime, 0));

}

void ACoin::OnCollect()
{
	Super::OnCollect();  
	RotationRate = CollectRotationRate; 
	GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &ACoin::DeathTimerComplete, 0.5f,false);  
}

void ACoin::DeathTimerComplete()
{
	AFPSGameMode* Gamemode = Cast<AFPSGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (Gamemode) {
		Gamemode->CurrentWidget->SetScore(Points);
	}
	Destroy(); 
}
