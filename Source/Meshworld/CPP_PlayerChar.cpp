// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_PlayerChar.h"
#include "Components/InputComponent.h"

// Sets default values
ACPP_PlayerChar::ACPP_PlayerChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_PlayerChar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_PlayerChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Move the character according to MoveForward and MoveRight
	if (!Velocity.IsZero())
	{
		FVector NewLocation = GetActorLocation() + GetActorForwardVector()*(SpeedScale * DeltaTime);
		SetActorLocation(NewLocation);
	}

}

// Called to bind functionality to input
void ACPP_PlayerChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Input for movement
	InputComponent->BindAxis("MoveForward", this, &ACPP_PlayerChar::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ACPP_PlayerChar::MoveRight);
}

void ACPP_PlayerChar::MoveForward(float AxisValue)
{
	Velocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * SpeedScale;
}

void ACPP_PlayerChar::MoveRight(float AxisValue)
{
	Velocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * SpeedScale;
}
