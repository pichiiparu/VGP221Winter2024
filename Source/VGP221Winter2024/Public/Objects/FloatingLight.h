#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PointLightComponent.h" // Include PointLightComponent header
#include "FloatingLight.generated.h"

UCLASS()
class VGP221WINTER2024_API AFloatingLight : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AFloatingLight();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY(VisibleAnywhere)
    UPointLightComponent* LightComponent; 
};
