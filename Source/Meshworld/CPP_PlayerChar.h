// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "CPP_PlayerChar.generated.h"

UCLASS()
class MESHWORLD_API ACPP_PlayerChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPP_PlayerChar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Input funtions
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	//void Restart();

	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

private:
	UPROPERTY(EditAnywhere, Category = "Character functionality")
	USceneComponent* OurVisibleComponent;

	UPROPERTY(EditAnywhere, Category = "Character Stats")
		float Health = 100;

	//Decal on cursorlocation
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		UDecalComponent* CursorToWorld;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	//Collision shape
	UShapeComponent* CollisionBox = nullptr;
	UShapeComponent* SwordCollision = nullptr;
};
