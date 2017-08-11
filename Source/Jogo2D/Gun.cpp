// Fill out your copyright notice in the Description page of Project Settings.

#include "Gun.h"
#include "PaperSpriteComponent.h"
#include "Engine/World.h"
#include "Bullet.h"


// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sprite = CreateDefaultSubobject
		<UPaperSpriteComponent>(TEXT("Sprite"));
	Sprite->SetCollisionProfileName("NoCollision");
	RootComponent = Sprite;


}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
	AmmoAmount = 20;
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::StartFire()
{
	UE_LOG(LogTemp, Warning, TEXT("START FIRE"));
	DoFire();
}

void AGun::StopFire()
{
	UE_LOG(LogTemp, Warning, TEXT("STOP FIRE"));
}

void AGun::DoFire()
{
	if (AmmoAmount > 0) {
		UWorld* World = GetWorld();
		if (World != nullptr) {
			FActorSpawnParameters SpawnParam;
			ABullet* Bullet = World->SpawnActor
				<ABullet>(BulletBP,
					RootComponent->GetComponentLocation(),
					FRotator::ZeroRotator, SpawnParam);
			AmmoAmount--;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("DO FIRE"));

}

void AGun::SetAmmoAmount(int NewAmount)
{
	AmmoAmount = NewAmount;
}

int AGun::GetAmmoAmount()
{
	return AmmoAmount;
}

