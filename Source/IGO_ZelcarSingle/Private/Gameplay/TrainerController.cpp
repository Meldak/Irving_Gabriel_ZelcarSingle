// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/TrainerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"



ATrainerController::ATrainerController():
	// Initialize Default Variables
	LookingRate(1.f)
{
}

void ATrainerController::BeginPlay()
{
	Super::BeginPlay();
}


void ATrainerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Setup Mapping Context On Possess
	SetupMappingContext();
}

void ATrainerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	// when inizializing input component, setup bind action inputs
	if (TObjectPtr<UEnhancedInputComponent> EIComponent = Cast<UEnhancedInputComponent>(InputComponent)) // Cast to Enhanced Input Component...
	{
		// if successful, setup bind action inputs
		SetupBindActionInput(EIComponent); // Pass Enhanced Input Component as parameter
	}
}

void ATrainerController::SetupMappingContext()
{
	// Get the Enhanced Input Local Player Subsystem from the Local Player related to this Player Controller
	if (TObjectPtr<UEnhancedInputLocalPlayerSubsystem> Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (!Main_IMC) return; // If is not set a valid Input Mapping Context, return
		Subsystem->AddMappingContext(Main_IMC, 0); // Add Main Input Mapping Context
	}
}


void ATrainerController::SetupBindActionInput(TObjectPtr<UEnhancedInputComponent> EIC)
{
	// Bind All Action Inputs to Functions 
	if (IA_Move) EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ATrainerController::MoveTrainer);
	if (IA_LookDirection)EIC->BindAction(IA_LookDirection, ETriggerEvent::Triggered, this, &ATrainerController::LookTrainer);
	if (IA_Jump) EIC->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &ATrainerController::JumpTrainer);
	if (IA_Sprint){
		EIC->BindAction(IA_Sprint, ETriggerEvent::Triggered, this, &ATrainerController::SprintTrainer);
		EIC->BindAction(IA_Sprint, ETriggerEvent::Completed, this, &ATrainerController::SprintTrainer);
	}

}

void ATrainerController::MoveTrainer(const FInputActionValue& Value)
{
	if (!GetCharacter()) return; // Ensure Character is valid

	const FVector2D MoveAxis = Value.Get<FVector2D>(); // Get 2D Vector from Input Action Value
	FRotator ViewRotation = GetControlRotation(); // Get Control Rotation from Player Controller
	// We only care about yaw rotation for movement
	ViewRotation.Pitch = 0.f;
	ViewRotation.Roll = 0.f;

	// Get Forward and Right Vectors from View Rotation
	const FVector Forward = FRotationMatrix(ViewRotation).GetUnitAxis(EAxis::X);
	const FVector Right = FRotationMatrix(ViewRotation).GetUnitAxis(EAxis::Y);

	// Add Movement Input to Character
	GetCharacter()->AddMovementInput(Forward, MoveAxis.X);
	GetCharacter()->AddMovementInput(Right, MoveAxis.Y);

}

void ATrainerController::LookTrainer(const FInputActionValue& Value)
{
	if (!GetCharacter()) return; // Ensure Character is valid
	FVector2D LookAxis = Value.Get<FVector2D>(); // Get 2D Vector from Input Action Value

	GetCharacter()->AddControllerYawInput(LookAxis.Y * LookingRate); // Add Yaw Input
	GetCharacter()->AddControllerPitchInput((LookAxis.X * -1) * LookingRate); // Add Pitch Input (Inverted)
	
}

void ATrainerController::JumpTrainer(const FInputActionValue& Value)
{
	GetCharacter()->Jump(); // Make Character Jump
}

void ATrainerController::SprintTrainer(const FInputActionValue& Value)
{
	bool bIsSprinting = Value.Get<bool>(); // Get Boolean from Input Action Value

	if (bIsSprinting){
		GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = 1200; // Increase Walk Speed while Sprinting
	}
	else {
		GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = 600; // Reset Walk Speed when not Sprinting
	}
}
