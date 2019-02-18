// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_PlayerChar.h"
#include "Components/InputComponent.h"
#include "Components/Decalcomponent.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Engine/Classes/GameFramework/PlayerController.h"

// Sets default values
ACPP_PlayerChar::ACPP_PlayerChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create a rootcomponent we can attach things to
	RootComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));

	//Create a crosshair in the world
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

}

// Called when the game starts or when spawned
void ACPP_PlayerChar::BeginPlay()
{
	Super::BeginPlay();

	//Show system cursor. Should probably be false
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
}

// Called every frame
void ACPP_PlayerChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FHitResult Hit;
	bool HitResult = false;

	HitResult = GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_WorldStatic), true, Hit);

	if (HitResult)
	{
		///Updates cursor
		FVector CursorFV = Hit.ImpactNormal;
		FRotator CursorR = CursorFV.Rotation();
		CursorToWorld->SetWorldLocation(Hit.Location);
		CursorToWorld->SetWorldRotation(CursorR);

		///Set the new direction of the pawn:
		FVector CursorLocation = Hit.Location;
		UE_LOG(LogTemp, Warning, TEXT("Hit location %s!"), *Hit.Location.ToString());
		///Set Z to a little above ground
		FVector TempLocation = FVector(CursorLocation.X, CursorLocation.Y, 30.f);

	
		
	}
}

// Called to bind functionality to input
void ACPP_PlayerChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Input for movement
	InputComponent->BindAxis("MoveForward", this, &ACPP_PlayerChar::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ACPP_PlayerChar::MoveRight);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ACPP_PlayerChar::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACPP_PlayerChar::StopJumping);
}

void ACPP_PlayerChar::MoveForward(float AxisValue)
{
	FVector cameraForward = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraRotation().Vector();

	cameraForward.Z = 0.0f;
	cameraForward.Normalize();

	if (AxisValue != 0.0f)
	{
		AddMovementInput(cameraForward, AxisValue);
	}
}

void ACPP_PlayerChar::MoveRight(float AxisValue)
{
	if ((Controller != NULL) && (AxisValue != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, AxisValue);
	}
}

