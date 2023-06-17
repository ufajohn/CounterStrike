// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class COUNTERSTRIKE_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float Value);
	void RotateRight(float Value);
	void RotateTurret(float Value);

	UPROPERTY(EditAnywhere, Category = "Components")
	class UStaticMeshComponent* TankBodyMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UStaticMeshComponent* TankTurretMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UStaticMeshComponent* LeftTrackMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UStaticMeshComponent* RightTrackMesh;

	float MoveSpeed;
	float RotateSpeed;
	float TurretRotateSpeed;
};
