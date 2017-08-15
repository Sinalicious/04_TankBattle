// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"
#include "Engine/World.h"
#include "TankPlayerController.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "BattleTank.h"


void ATankAiController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAiController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (PlayerTank) {
		
		MoveToActor(PlayerTank, AcceptanceRadius); //TODO check readius is in cm

		// Aim towards the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		// Fire if ready
		ControlledTank->Fire(); // TODO limit firing rates
	}
}






