// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CPP_EnemyChaser.generated.h"

UCLASS()
class MESHWORLD_API ACPP_EnemyChaser : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACPP_EnemyChaser();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FVector MoveDirection = FVector(1.f, 0.f, 0.f);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
		float Speed = 200.f;

	UPROPERTY(EditAnywhere)
		float Health = 100.f;

	UPROPERTY(EditAnywhere)
		UShapeComponent* RootBox = nullptr;
};
