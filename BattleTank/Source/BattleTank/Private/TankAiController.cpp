// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankAimingComponent.h"
#include "BattleTank.h"


void ATankAiController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAiController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank) && (ControlledTank)) { return; }
		
		MoveToActor(PlayerTank, AcceptanceRadius); //TODO check readius is in cm

		// Aim towards the player
		auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		// TODO Fix firing
		// ControlledTank->Fire(); // TODO limit firing rates
}






