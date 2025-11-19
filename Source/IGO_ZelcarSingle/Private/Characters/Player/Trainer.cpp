// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/Trainer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


// Sets default values
ATrainer::ATrainer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(34.f, 88.f);
	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// Calling setup functions to configure components
	SetupDefaultMovementComponent();
	SetupSpringArmComponent();
	SetupFollowCameraComponent();

}

// Called to bind functionality to input
void ATrainer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Called when the game starts or when spawned
void ATrainer::BeginPlay()
{
	Super::BeginPlay();

}

// Called when actor is constructed
void ATrainer::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

// Called every frame
void ATrainer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ATrainer::SetupFollowCameraComponent()
{
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera")); //create camera component
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	if (CameraBoom)	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the spring arm
}

void ATrainer::SetupSpringArmComponent()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom")); // Create spring arm component
	CameraBoom->SetupAttachment(RootComponent); // Attach the spring arm to the root component
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	//CameraBoom->SetRelativeRotation(FRotator(-10.f, 0.f, 0.f)); // Rotate the arm slightly downward
	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	CameraBoom->bInheritPitch = true; // We want the arm to inherit pitch rotation
	CameraBoom->bInheritYaw = true; // We want the arm to inherit yaw rotation
	CameraBoom->bInheritRoll = false; // We don't want the arm to inherit roll rotation

	CameraBoom->TargetArmLength = 600.f; // The camera follows at this distance behind the character
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 80.f); // Offset the camera upwards
	CameraBoom->TargetOffset = FVector(0.f, 0.f, 0.f); // No target offset
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level
}

void ATrainer::SetupDefaultMovementComponent()
{
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f); // ...at this rotation rate
	GetCharacterMovement()->bConstrainToPlane = true; // Constrain movement to a plane
	GetCharacterMovement()->bSnapToPlaneAtStart = true; // Snap to plane at start
}




