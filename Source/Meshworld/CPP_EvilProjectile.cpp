// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_EvilProjectile.h"

// Sets default values
ACPP_EvilProjectile::ACPP_EvilProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_EvilProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACPP_EvilProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

