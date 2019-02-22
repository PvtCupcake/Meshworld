// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_EnemyChaser.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values
ACPP_EnemyChaser::ACPP_EnemyChaser()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	///A standard box collider with Overlap Events:
	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MyEnemy"));
	RootComponent = RootBox;
	RootBox->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ACPP_EnemyChaser::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACPP_EnemyChaser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveDirection = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - GetActorLocation();
	MoveDirection.Normalize();
	SetActorRotation(MoveDirection.Rotation());
	FVector NewLocation = GetActorLocation();
	NewLocation += (MoveDirection * Speed * DeltaTime);
	SetActorLocation(NewLocation);

}

// Called to bind functionality to input
void ACPP_EnemyChaser::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

