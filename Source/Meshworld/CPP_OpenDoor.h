// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/TriggerVolume.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPP_OpenDoor.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MESHWORLD_API UCPP_OpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCPP_OpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UFUNCTION(BlueprintCallable, Category = "OpenDoor")
		void OpentheDoor();

	UPROPERTY(EditAnywhere)
		float OpenDoorMovement = 500.0f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate;
		
	UPROPERTY(EditAnywhere)
		AActor* ActorThatOpens;
};
