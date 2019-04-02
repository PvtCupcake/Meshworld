// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CPP_EnemyTurret.generated.h"

UCLASS()
class MESHWORLD_API ACPP_EnemyTurret : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACPP_EnemyTurret();

	FVector MoveDirection = FVector(0.f, 0.f, 0.f);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Spawning") //Sets the spawning tab in the blueprint of player, where you can choose what to shoot       
		TSubclassOf<class ACPP_EvilProjectile> BulletBlueprint;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category="Shoot")
		void Shooting();

	UFUNCTION(BlueprintCallable, Category = "Turning")
		void Turning();

private:

	UPROPERTY(EditAnywhere)
		UShapeComponent* RootSphere = nullptr;

	UPROPERTY(EditAnywhere)
		float ShootDelayMax = 2.f;

	UPROPERTY(EditAnywhere)
		float ShootDelayMin = 1.f;

	float CurrentShootDelay = 0.f;
};
