// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_OpenDoor.h"
#include "CPP_PlayerChar.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UCPP_OpenDoor::UCPP_OpenDoor()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UCPP_OpenDoor::BeginPlay()
{
	Super::BeginPlay(); 

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UCPP_OpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpentheDoor();
	}
}

void UCPP_OpenDoor::OpentheDoor()
{
	AActor* Owner = GetOwner();

	FRotator NewRotation = FRotator(0.f, -90.f, 0.f);

	Owner->AddActorLocalRotation(NewRotation);

	PressurePlate->SetActorEnableCollision(false);

	GetWorld()->GetTimerManager().SetTimer(pressureplateTimerHandle, this, &UCPP_OpenDoor::ActivatePressureplate, DoorTimer, false);
}

void UCPP_OpenDoor::ActivatePressureplate()
{
	AActor* Owner = GetOwner();

	FRotator NewRotation = FRotator(0.f, 90.f, 0.f);

	Owner->AddActorLocalRotation(NewRotation);

	PressurePlate->SetActorEnableCollision(true);
}
