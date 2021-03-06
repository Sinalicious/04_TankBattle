// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Math/UnrealMathUtility.h"
#include "BattleTank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay() {
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) 
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0) {
		OnDeath.Broadcast();
	}

	return DamageToApply;
}

float ATank::GetHealthPercent() const 
{
	return (float)CurrentHealth / (float)StartingHealth;
}

// used for testing with key bindings
void ATank::IncreaseHealth()
{
	if (CurrentHealth == StartingHealth) { return; }
	else {
		CurrentHealth = CurrentHealth + 20;
	}
}
// used for testing with key bindings
void ATank::DecreaseHealth()
{
	if (CurrentHealth <= 20) { return; }
	else {
		CurrentHealth = CurrentHealth - 20;
	}
}

void ATank::PickupHealth(int32 HealthValue) 
{
	if (HealthValue != 0) {
		if (CurrentHealth < StartingHealth) {
			CurrentHealth += HealthValue;
			if (CurrentHealth > StartingHealth) {
				CurrentHealth = StartingHealth;
			}
		}
	}
}