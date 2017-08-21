// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()
public:
	
	// Called by thhe engine when actor damage is dealt
	virtual float TakeDamage (float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	// Return current health
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	UPROPERTY(BlueprintAssignable)
	FTankDelegate OnDeath;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void IncreaseHealth();

	UFUNCTION(BlueprintCallable, Category = "Health")
	void DecreaseHealth();

	void PickupHealth(int32 HealthValue);

	UPROPERTY(EditAnywhere, Category = "Health")
	int32 StartingHealth = 100;

	UPROPERTY(EditAnywhere, Category = "Health")
	int32 CurrentHealth = 0;

private:
	ATank();

	virtual void BeginPlay() override;
};
