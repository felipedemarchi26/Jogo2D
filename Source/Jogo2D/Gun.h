// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class JOGO2D_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float TimeRate;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void StartFire();
	virtual void StopFire();
	virtual void DoFire();
	void SetAmmoAmount(int NewAmount);
	int GetAmmoAmount();

private:

	UPROPERTY(EditAnywhere)
		int AmmoAmount;

	UPROPERTY(EditAnywhere)
		class UPaperSpriteComponent* Sprite;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABullet> BulletBP;

	FTimerHandle KeepShotting;
	
	
};
