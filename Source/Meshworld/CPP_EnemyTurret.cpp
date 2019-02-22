// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_EnemyTurret.h"
#include "CPP_EvilProjectile.h"
#include "Components/SphereComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values
ACPP_EnemyTurret::ACPP_EnemyTurret()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	///A standard box collider with Overlap Events:
	RootSphere = CreateDefaultSubobject<USphereComponent>(TEXT("MyEnemy"));
	RootComponent = RootSphere;
	RootSphere->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ACPP_EnemyTurret::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_EnemyTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveDirection = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - GetActorLocation();
	MoveDirection.Normalize();
	SetActorRotation(MoveDirection.Rotation());

	CurrentShootDelay -= DeltaTime;

	if (CurrentShootDelay < 0.f)
	{
		Shooting();

		CurrentShootDelay = FMath::FRandRange(ShootDelayMin, ShootDelayMax);
	}
}

// Called to bind functionality to input
void ACPP_EnemyTurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACPP_EnemyTurret::Shooting()
{
	UWorld* World = GetWorld();
	if (World)
	{
		FVector Location = 	GetActorLocation();
		World->SpawnActor<ACPP_EvilProjectile>(BulletBlueprint, Location, GetActorRotation());
	}

}

