// Fill out your copyright notice in the Description page of Project Settings.


#include "Hazards/Hazard.h"
#include "GameFramework/Character.h" 
#include "Player/FPSCharacter.h"  
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AHazard::AHazard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
    RootComponent = CollisionComponent;

    // Set up overlap events 
    CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AHazard::OnOverlapBegin);    
    CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &AHazard::OnOverlapEnd);   
}

void AHazard::EnterHazard(ACharacter* PlayerCharacter)
{
    if (PlayerCharacter)
    {
        PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = 300.0f;
        AFPSCharacter* PlayerRef = Cast<AFPSCharacter>(PlayerCharacter);
        if (PlayerRef)
        {
            PlayerRef->inWater = true;
            PlayerRef->isSprinting = false;
        }
    }
}

void AHazard::ExitHazard(ACharacter* PlayerCharacter)
{
    if (PlayerCharacter)
    { 
        PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = 600.0f;
        AFPSCharacter* PlayerRef = Cast<AFPSCharacter>(PlayerCharacter); 
        if (PlayerRef) 
        {
            PlayerRef->inWater = false; 
        } 
    }
}

void AHazard::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor->ActorHasTag("Player") && OtherActor != this)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Player In Hazard!"))); 
        ACharacter* PlayerCharacter = Cast<ACharacter>(OtherActor); 
        if (PlayerCharacter)
        {
            EnterHazard(PlayerCharacter); 
        }
    }
} 

void AHazard::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor->ActorHasTag("Player") && OtherActor != this)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Player Exits Hazard!")));
        ACharacter* PlayerCharacter = Cast<ACharacter>(OtherActor);
        if (PlayerCharacter)
        {
            ExitHazard(PlayerCharacter);
        }
    }
} 


