// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/PostProcessComponent.h"  
#include "Materials/MaterialInterface.h"  
#include "GameFramework/Character.h"
#include "Projectile/FPSProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "FPSGameMode.h"
#include "Engine/DamageEvents.h" 
#include "GameFramework/CharacterMovementComponent.h" 
#include "FPSCharacter.generated.h"


UCLASS()
class VGP221WINTER2024_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	//#include "GameFramework/CharacterMovementComponent.h"  if i want to use another method of character movement
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(VisibleAnywhere)
	ACharacter* characterComponent; 

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPSCameraComponent;

	UPROPERTY(EditAnywhere) 
	UCapsuleComponent* CollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	USkeletalMeshComponent* FPSMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	FVector MuzzleOffset;

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* Collider; 

	// Connecting a prefab in blueprints. Similar to Unity gameobjects drag and drop
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<class AFPSProjectile> ProjectileClass;

	UFUNCTION()
	void MoveForward(float value);

	UFUNCTION()
	void MoveRightNotTheSameName(float value);

	void StartJump();
	void EndJump();

	void StartSprinting();
	void EndSprinting(); 

	void StartCrouch(); 
	void EndCrouch(); 

	void Fire();

	void Dash(); 
	void ResetDashCooldown(); 
	void ResetDashLocation(); 

	void GameOverDelayed(); 

	// Temp health code
	float Health = 100;
	const float MaxHealth = 100;

	// Sprint / Movement 
	bool isSprinting;
	float sprintSpeed = 1000.0f; 
	float walkSpeed = 600.0f; 

	float BaseSpeed = 600.0f; 
	float MaxSpeed = 10000.0f;
	float AccelerationRate = 500.0f; 
	float CurrentSpeed = BaseSpeed; 

	//Dash
	FTimerHandle DashCooldownTimerHandle;
	FTimerHandle DashResetTimerHandle; 
	FVector InitialVelocity;   
	float DashAcceleration = 10.0f; 
	float DashDuration = 0.2f; 
	float DashCooldown = 5.0f;
	float DashKnockbackForce = 5000.0f; 
	bool isDashing = false; 
	bool bCanDash = true; 
	bool inWater = false; 

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override; 

	UFUNCTION()
	void HitObject(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);  

	UFUNCTION() 
	void ApplyWaterPostProcessMaterial(bool bApply);     

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PostProcessing")
	UPostProcessComponent* PostProcessComponent;  

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	UMaterialInterface* WaterPostProcessMaterial;
	 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio") 
	USoundBase* DashSound;  
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* DamagedSound;

};
