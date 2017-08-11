// Fill out your copyright notice in the Description page of Project Settings.

#include "Personagem.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "PaperFlipbookComponent.h"
#include "Components/ChildActorComponent.h"
#include "Gun.h"

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

	Gun = CreateDefaultSubobject
		<UChildActorComponent>(TEXT("Gun"));
	Gun->SetupAttachment(GetSprite());

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
	PlayerInputComponent->BindAction("Fire", IE_Pressed,
		this, &APersonagem::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released,
		this, &APersonagem::StopFire);

	PlayerInputComponent->BindTouch(IE_Pressed, this,
		&APersonagem::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this,
		&APersonagem::TouchStopped);

}

void APersonagem::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateFlipbook();

}

void APersonagem::UpdateFlipbook()
{

	if (GetVelocity().X != 0) {
		GetSprite()->SetFlipbook(Walking);
		if (GetVelocity().X > 0) {
			GetSprite()->SetWorldRotation(FRotator(0.0f, 0.0f, 0.0f));
		} else if (GetVelocity().X < 0) {
			GetSprite()->SetWorldRotation(FRotator(0.0f, 180.0f, 0.0f));
		}
	} else {
		GetSprite()->SetFlipbook(Idle);
	}

}

void APersonagem::StartFire()
{

	if (Gun != nullptr) {
		if (Gun->GetChildActor()->IsA(AGun::StaticClass())) {
			AGun* GunCast = Cast<AGun>(Gun->GetChildActor());
			GunCast->StartFire();
		}
	}

}

void APersonagem::StopFire()
{
	if (Gun != nullptr) {
		if (Gun->GetChildActor()->IsA(AGun::StaticClass())) {
			AGun* GunCast = Cast<AGun>(Gun->GetChildActor());
			GunCast->StopFire();
		}
	}
}

void APersonagem::Move(float Value)
{
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
}

void APersonagem::TouchStarted(const ETouchIndex::Type FinderIndex, const FVector Location)
{

	Jump();

}

void APersonagem::TouchStopped(const ETouchIndex::Type FinderIndex, const FVector Location)
{

	StopJumping();

}


