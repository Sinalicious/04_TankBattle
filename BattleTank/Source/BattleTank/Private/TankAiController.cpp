// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAiController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h" // So we can implement OnDeath
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

		if (AimingComponent->GetFiringState() == EFiringState::Locked) {
			AimingComponent->Fire();
		}
}

void ATankAiController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto PosessedTank = Cast<ATank>(InPawn);
		if (!ensure(PosessedTank)) { return; }

		// Subscribe our local method to the deaths event
		PosessedTank->OnDeath.AddUniqueDynamic(this, &ATankAiController::OnTankDeath);

	}
}

void ATankAiController::OnTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Recieved"));
}






