#include "Objects/FloatingLight.h"

// Sets default values
AFloatingLight::AFloatingLight()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    LightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("Point Light")); // Create PointLightComponent
    //RootComponent = LightComponent; // Attach PointLightComponent to root
    LightComponent->SetupAttachment(RootComponent); 
    LightComponent->SetMobility(EComponentMobility::Movable); 
    static ConstructorHelpers::FObjectFinder<UPointLightComponent> PointLightAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube")); 
    LightComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f)); 
}

// Called when the game starts or when spawned
void AFloatingLight::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AFloatingLight::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    UE_LOG(LogTemp, Warning, TEXT("Floating Light")); 
    FVector NewLocation = GetActorLocation(); 
    FRotator NewRotation = GetActorRotation(); 
    float RunningTime = GetGameTimeSinceCreation(); 
    float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime)); 
    NewLocation.Z += DeltaHeight * 50.0f;        //Scale our height by a factor of 20
    float DeltaRotation = DeltaTime * 20.0f;    //Rotate by 20 degrees per second
    NewRotation.Yaw += DeltaRotation; 
    SetActorLocationAndRotation(NewLocation, NewRotation); 

    float frequency = 0.5f; 
    // Calculate the brightness based on a sine function to make it fade and go bright
    float Brightness = FMath::Abs(FMath::Sin((RunningTime + DeltaTime) * frequency));
    Brightness *= 100000.0f; 
    // Set the brightness of the light component
    LightComponent->SetIntensity(Brightness);

    RunningTime += DeltaTime;
}
