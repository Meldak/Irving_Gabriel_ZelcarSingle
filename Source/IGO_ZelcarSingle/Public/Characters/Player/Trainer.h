// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Trainer.generated.h"

// Forward Declarations
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class IGO_ZELCARSINGLE_API ATrainer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATrainer();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called when actor is constructed (after properties are set)
	virtual void OnConstruction(const FTransform& Transform) override;

private:
	// Setup configuration to Follow Camera
	void SetupFollowCameraComponent();
	// Setup configuration to Spring Arm
	void SetupSpringArmComponent();
	// Setup default movement component settings
	void SetupDefaultMovementComponent();

private:
	// Create objects reference for Spring Arm Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Trainer|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;
	// Create objects reference for Follow Camera Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trainer|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

public:	

};
