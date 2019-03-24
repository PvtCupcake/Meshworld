// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_EnemyCharChaser.h"

// Sets default values
ACPP_EnemyCharChaser::ACPP_EnemyCharChaser()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_EnemyCharChaser::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_EnemyCharChaser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPP_EnemyCharChaser::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

