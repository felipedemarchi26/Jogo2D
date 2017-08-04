// Fill out your copyright notice in the Description page of Project Settings.

#include "Personagem.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "PaperFlipbookComponent.h"

APersonagem::APersonagem() {
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>
		(TEXT("CameraBoom"));
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>
		(TEXT("Camera"));
	Camera->ProjectionMode = ECameraProjectionMode::Orthographic;
	Camera->OrthoWidth = 2048.0f;
	Camera->SetupAttachment(CameraBoom);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void APersonagem::BeginPlay()
{
	Super::BeginPlay();

	if (Idle) {
		GetSprite()->SetFlipbook(Idle);
	}
}

void APersonagem::SetupPlayerInputComponent(UInputComponent * 
	PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Move", this, &APersonagem::Move);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this,
		&APersonagem::Jump);

}

void APersonagem::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GetVelocity().X > 0) {
		GetSprite()->SetWorldRotation(FRotator(0.0f, 0.0f, 0.0f));
	} else if (GetVelocity().X < 0) {
		GetSprite()->SetWorldRotation(FRotator(0.0f, 180.0f, 0.0f));
	}

	UpdateFlipbook();

}

void APersonagem::UpdateFlipbook()
{

	if (GetVelocity().X != 0) {
		GetSprite()->SetFlipbook(Walking);
	} else {
		GetSprite()->SetFlipbook(Idle);
	}

}

void APersonagem::Move(float Value)
{
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
}


