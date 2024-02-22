// Fill out your copyright notice in the Description page of Project Settings.


#include "Hazards/Hazard.h"
#include "GameFramework/Character.h" 
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

void AHazard::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor->ActorHasTag("Player") && OtherActor != this)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Player In Hazard!")));
        ACharacter* playerCharacter = Cast<ACharacter>(OtherActor);       
        if (playerCharacter)    
        {   
            // Set the MaxWalkSpeed property directly
            playerCharacter->GetCharacterMovement()->MaxWalkSpeed = 300.0f;       
        } 
    }
}

void AHazard::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor->ActorHasTag("Player") && OtherActor != this)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Player Exits Hazard!")));
        ACharacter* playerCharacter = Cast<ACharacter>(OtherActor);
        if (playerCharacter)
        {
            // Set the MaxWalkSpeed property directly
            playerCharacter->GetCharacterMovement()->MaxWalkSpeed = 600.0f;
        }
    }
}

// Called when the game starts or when spawned
void AHazard::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHazard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

