// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TankBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TankBodyMesh"));
	SetRootComponent(TankBodyMesh);

	TankTurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TankTurretMesh"));
	TankTurretMesh->SetupAttachment(TankBodyMesh);

	LeftTrackMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftTrackMesh"));
	LeftTrackMesh->SetupAttachment(TankBodyMesh);

	RightTrackMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightTrackMesh"));
	RightTrackMesh->SetupAttachment(TankBodyMesh);

	MoveSpeed = 100.0f;
	RotateSpeed = 100.0f;
	TurretRotateSpeed = 100.0f;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATank::MoveForward);
	PlayerInputComponent->BindAxis("RotateRight", this, &ATank::RotateRight);
	PlayerInputComponent->BindAxis("RotateTurret", this, &ATank::RotateTurret);
}

void ATank::MoveForward(float Value)
{
	FVector MoveDirection = GetActorForwardVector();
	AddMovementInput(MoveDirection, Value * MoveSpeed);
}

void ATank::RotateRight(float Value)
{
	FRotator RotateDirection = FRotator(0.0f, Value * RotateSpeed, 0.0f);
	AddActorLocalRotation(RotateDirection);
}

void ATank::RotateTurret(float Value)
{
	FRotator TurretRotation = FRotator(0.0f, Value * TurretRotateSpeed, 0.0f);
	TankTurretMesh->AddLocalRotation(TurretRotation);
}

