// Copyright Sin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ShapeComponent.h"
#include "HPPickup.generated.h"

UCLASS()
class BATTLETANK_API AHPPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	AHPPickup();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// static mesh for the pickup
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MyPickup;

	UPROPERTY(EditAnywhere)
	USceneComponent* PickupRoot;

	UPROPERTY(EditAnywhere)
	UShapeComponent* PickupBox;

	UFUNCTION()
	void OnPlayerEnterPickupBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyInted, bool bFromSweep, const FHitResult& SweepResult);
	
	// UFUNCTION(BlueprintCallable, Category = "Health")
	// void IncreaseHealth();

	void IncreaseHealth(class ATank* Tank);

	bool CanBePicked(ATank* Tank) const;

private:
	UPROPERTY(EditDefaultsOnly, Category = "HealthValue")
	int32 HealthValue = 20;
};
