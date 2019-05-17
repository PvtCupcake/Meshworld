// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_PlayerChar.h"
#include "CPP_EvilProjectile.h"
#include "CPP_EnemyChaser.h"

#include "Components/InputComponent.h"
#include "Components/Decalcomponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Engine/Classes/GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACPP_PlayerChar::ACPP_PlayerChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create a crosshair in the world
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(GetCapsuleComponent());


	// NOTE(Kris) Please don't hardcode this path, it leads to errors
	// Make it a blueprint property
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/Assets/Player/UI/M_Cursor_Decal.M_Cursor_Decal'"));
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

	CollisionBox = this->FindComponentByClass<UCapsuleComponent>();

	if (CollisionBox)
	{
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACPP_PlayerChar::OnOverlap);
	}

	SwordCollision = this->FindComponentByClass<UBoxComponent>();
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

		///Set the new direction of the character:
		FVector CursorLocation = Hit.Location;
		//UE_LOG(LogTemp, Warning, TEXT("Hit location %s!"), *Hit.Location.ToString());
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
	if (AxisValue != 0.0f)
	{
		const FRotator Rotation = GetActorRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, AxisValue);
	}
}

void ACPP_PlayerChar::MoveRight(float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		const FRotator Rotation = GetActorRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, AxisValue);
	}
}

void ACPP_PlayerChar::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent,
								int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(ACPP_EvilProjectile::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Hit"))
			Health = Health - 50;
			OtherActor->Destroy();
	}
	if (OtherActor->IsA(ACPP_EnemyChaser::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Hit by chaser"))
			Health = Health - 25;
	}
	/*if (OverlappedComponent->IsA(SwordCollision())	Work in progress
	{

	}*/
}

/*void ACPP_PlayerChar::Restart()						Player becomes imobile if uncommented
{
	if (Health <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Dead"))
	}
}*/