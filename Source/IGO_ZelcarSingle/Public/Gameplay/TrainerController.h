// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"

#include "TrainerController.generated.h"

/**
 * 
 */

 // Forward Declarations
class UEnhancedInputComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class IGO_ZELCARSINGLE_API ATrainerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATrainerController(); // Trainer Controll Constructor

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override; // Possess Override
	virtual void SetupInputComponent() override; // Setup Input Component Override


private:
	// Input Actions and Mapping Context

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Trainer|Inputs", meta = (AllowPrivateAccess="true"))
	TObjectPtr<const UInputAction> IA_Move;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Trainer|Inputs", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<const UInputAction> IA_LookDirection;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Trainer|Inputs", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<const UInputAction> IA_Jump;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Trainer|Inputs", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<const UInputAction> IA_Sprint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Trainer|Inputs", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<const UInputMappingContext> Main_IMC; // Main Input Mapping Context

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Trainer|Inputs", meta = (AllowPrivateAccess = "true"))
	float LookingRate; // Sensitivity Look Rate

private:
	// Setup Input Functions 
	void SetupMappingContext(); // Setup Mapping Context
	void SetupBindActionInput(TObjectPtr<UEnhancedInputComponent> EIC); // Setup Bind Action Inputs

	UFUNCTION()
	void MoveTrainer(const FInputActionValue& Value); // Move Trainer Bind Function
	UFUNCTION()
	void LookTrainer(const FInputActionValue& Value); // Look Trainer Bind Function
	UFUNCTION()
	void JumpTrainer(const FInputActionValue& Value); // Jump Trainer Bind Function
	UFUNCTION()
	void SprintTrainer(const FInputActionValue& Value); // Sprint Trainer Bind Function

};
