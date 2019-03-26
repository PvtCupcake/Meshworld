// Fill out your copyright notice in the Description page of Project Settings.

#include "CollectiblePage.h"

// Sets default values
ACollectiblePage::ACollectiblePage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACollectiblePage::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollectiblePage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

