// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_PlayerPawn.h"
#include "Components/InputComponent.h"
//#include "Kismet/GameplayStatics.h"

// Sets default values
ACPP_PlayerPawn::ACPP_PlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create a crosshair in the world
	//CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	//CursorToWorld->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ACPP_PlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_PlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Move the character according to MoveForward and MoveRight
	if (!Velocity.IsZero())
	{
		FVector NewLocation = GetActorLocation() + (Velocity * SpeedScale * DeltaTime);
		SetActorLocation(NewLocation);
	}
}

// Called to bind functionality to input
void ACPP_PlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Input for movement
	InputComponent->BindAxis("MoveForward", this, &ACPP_PlayerPawn::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ACPP_PlayerPawn::MoveRight);
}

void ACPP_PlayerPawn::MoveForward(float AxisValue)
{
	Velocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * SpeedScale;
}

void ACPP_PlayerPawn::MoveRight(float AxisValue)
{
	Velocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * SpeedScale;
}

