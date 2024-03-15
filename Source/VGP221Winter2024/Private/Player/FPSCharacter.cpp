// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FPSCharacter.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PostProcessComponent = CreateDefaultSubobject<UPostProcessComponent>(TEXT("PostProcessComponent"));
	PostProcessComponent->SetupAttachment(GetCapsuleComponent()); 
	Collider = GetCapsuleComponent(); 
	Collider->OnComponentHit.AddDynamic(this, &AFPSCharacter::HitObject); 
	if (!FPSCameraComponent) {
		FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera")); // Instantiate in Unity. But only in constructors
		FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
		FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
		FPSCameraComponent->bUsePawnControlRotation = true;
	}

		
	/*
	if (!FPSMesh) {
		FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
		FPSMesh->SetupAttachment(FPSCameraComponent);
		FPSMesh->bCastDynamicShadow = false;
		FPSMesh->CastShadow = false;
	}
	*/ 

	GetMesh()->SetOwnerNoSee(true);
	UE_LOG(LogTemp, Warning, TEXT("Constructor Called from FPSCharacter"));

	//characterComponent->CrouchedEyeHeight = 0.5f; 
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	check(GEngine != nullptr)
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Spawning FPSCharacter")));
	GetCharacterMovement()->JumpZVelocity = 1000.0f;
	GetCharacterMovement()->AirControl = 1000.0f; 
	GetCharacterMovement()->GravityScale = 2.0f; 

	TArray<UPostProcessComponent*> PostProcessComponents;
	GetComponents<UPostProcessComponent>(PostProcessComponents);
	if (PostProcessComponents.Num() > 0)
	{
		PostProcessComponent = PostProcessComponents[0]; 
	}
	//PostProcessComponent->BlendWeight = 0.0f;   
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isSprinting) {
		CurrentSpeed += AccelerationRate * DeltaTime;
		CurrentSpeed = FMath::Clamp(CurrentSpeed, BaseSpeed, MaxSpeed);
		GetCharacterMovement()->MaxWalkSpeed = CurrentSpeed; 
	}

	if (inWater) PostProcessComponent->BlendWeight = 1.0f; 
	else PostProcessComponent->BlendWeight = 0.0f; 
}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Movement
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRightNotTheSameName); // Callback function doesn't need to be named the same

	// Look
	PlayerInputComponent->BindAxis("LookHorizontal", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookVertical", this, &AFPSCharacter::AddControllerPitchInput);

	// Jump
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::EndJump);

	// Fire
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);

	//Sprint
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AFPSCharacter::StartSprinting); 
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AFPSCharacter::EndSprinting); 

	//Crouch
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AFPSCharacter::StartCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AFPSCharacter::EndCrouch); 

	//Dash Forward
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &AFPSCharacter::Dash);
}

void AFPSCharacter::MoveForward(float value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, value);
}

void AFPSCharacter::MoveRightNotTheSameName(float value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, value);
}

void AFPSCharacter::StartJump()
{
	bPressedJump = true;
}

void AFPSCharacter::EndJump()
{
	bPressedJump = false;
}

void AFPSCharacter::StartSprinting()  
{
	if (inWater) return; 
	isSprinting = true; 
	if (GetCharacterMovement()) {
		CurrentSpeed += AccelerationRate;
		CurrentSpeed = FMath::Clamp(CurrentSpeed, BaseSpeed, MaxSpeed);
		GetCharacterMovement()->MaxWalkSpeed = CurrentSpeed;
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("Player Sprint Pressed")));
}

void AFPSCharacter::EndSprinting()
{
	if (inWater) return; 
	isSprinting = false; 
	if (GetCharacterMovement()) {
		CurrentSpeed = BaseSpeed;
		GetCharacterMovement()->MaxWalkSpeed = CurrentSpeed;
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("Player Sprint Released")));
}


void AFPSCharacter::StartCrouch()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Crouch Pressed"))); 
} 

void AFPSCharacter::EndCrouch()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Crouch Released")));
}

void AFPSCharacter::Fire()
{
	// Easy way to acccess the gamemode
	/*
	AFPSGameMode* Gamemode = Cast<AFPSGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (Gamemode) {
		Health -= 10;
		float HealthPercent = Health / MaxHealth;

		Gamemode->CurrentWidget->SetHealthBar(HealthPercent);
	}
	*/
	// Rest of the fire code
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Player Fired Pressed")));

	if (!ProjectileClass) return;

	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);

	MuzzleOffset.Set(100.0f, 0.0f, 0.0f);

	FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

	FRotator MuzzleRotation = CameraRotation;
	MuzzleRotation.Pitch += 5.0f;

	// Instantiate
	// 1. Get the world we want to spawn
	// 2. SpawnActor
	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);

		if (Projectile)
		{
			FVector LaunchDirection = MuzzleRotation.Vector();
			Projectile->FireInDirection(LaunchDirection);
		}
	} 
}

void AFPSCharacter::Dash()
{
	if (inWater) return; 
	if (bCanDash)
	{
		isDashing = true;  
		bCanDash = false;
		GetWorldTimerManager().SetTimer(DashCooldownTimerHandle, this, &AFPSCharacter::ResetDashCooldown, DashCooldown, false);
		InitialVelocity = GetCharacterMovement()->Velocity;

		FRotator CameraRotation = FPSCameraComponent->GetComponentRotation();
		FVector DashDirection = CameraRotation.Vector();
		FVector DashVelocity = DashDirection * CurrentSpeed * DashAcceleration;

		GetCharacterMovement()->Launch(DashVelocity);
		GetWorldTimerManager().SetTimer(DashResetTimerHandle, this, &AFPSCharacter::ResetDashLocation, DashDuration, false);
	}
}


void AFPSCharacter::ResetDashCooldown()
{
	bCanDash = true;
}

void AFPSCharacter::ResetDashLocation()
{
	GetCharacterMovement()->Velocity = InitialVelocity;   
	SetActorLocation(GetActorLocation());
	isDashing = false; 
}


float AFPSCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) 
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser); 

	// Easy way to acccess the gamemode 
	AFPSGameMode* Gamemode = Cast<AFPSGameMode>(UGameplayStatics::GetGameMode(GetWorld())); 
	if (Gamemode) { 
		Health -= DamageAmount; 
		float HealthPercent = Health / MaxHealth;  

		Gamemode->CurrentWidget->SetHealthBar(HealthPercent); 
	}
	 
	return FinalDamage;
}

void AFPSCharacter::HitObject(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) 
{
	// Collision with only physics objects
	if (OtherActor->ActorHasTag("Enemy") && isDashing)
	{
		AEnemyCharacter* enemyCharacter = Cast<AEnemyCharacter>(OtherActor);
		enemyCharacter->TakeDamage(25);
		FVector CameraForwardVector = FPSCameraComponent->GetForwardVector(); 
		FVector ImpulseDirection = -CameraForwardVector;  
		FVector KnockbackVelocity = ImpulseDirection * DashKnockbackForce;   
		GetCharacterMovement()->Launch(KnockbackVelocity); 
		UE_LOG(LogTemp, Warning, TEXT("Dashing Enemy")); 

		isDashing = false;
	} 
}

void AFPSCharacter::ApplyWaterPostProcessMaterial(bool bApply) 
{
	if (bApply)
	{
		PostProcessComponent->BlendWeight = 1.0f;  
	}
	else
	{
		PostProcessComponent->BlendWeight = 0.0f;  
	}
} 
