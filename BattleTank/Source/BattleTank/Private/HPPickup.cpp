// Copyright Sin

#include "HPPickup.h"
#include "Components/ShapeComponent.h"
#include "Components/BoxComponent.h"
#include "Tank.h"
#include "BattleTank.h"

// Sets default values
AHPPickup::AHPPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickupRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Pickup Root"));
	RootComponent = PickupRoot;

	MyPickup = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Pickup Mesh"));
	MyPickup->AttachToComponent(PickupRoot, FAttachmentTransformRules::SnapToTargetIncludingScale);

	PickupBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PickuoBox"));
	PickupBox->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	PickupBox->bGenerateOverlapEvents = true;
	PickupBox->OnComponentBeginOverlap.AddDynamic(this, &AHPPickup::OnPlayerEnterPickupBox);
	PickupBox->AttachToComponent(PickupRoot, FAttachmentTransformRules::SnapToTargetIncludingScale);

}

// Called when the game starts or when spawned
void AHPPickup::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHPPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHPPickup::OnPlayerEnterPickupBox(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyInted, bool bFromSweep, const FHitResult& SweepResult)
{
	// AActor* ActorThatHits = OtherActor;
	if (ATank* ActorThatHits = dynamic_cast<ATank*>(OtherActor)) {
		if (CanBePicked(ActorThatHits)) {
			UE_LOG(LogTemp, Warning, TEXT("pickup touched"));
			IncreaseHealth(ActorThatHits);
			Destroy();
		}
	}
}

void AHPPickup::IncreaseHealth(ATank * Tank)
{
	int32 HealthMissing = (Tank->StartingHealth) - (Tank->CurrentHealth);
	int32 ValueHealed = FMath::Clamp(HealthValue, 1, HealthMissing);

	Tank->PickupHealth(ValueHealed);
}

bool AHPPickup::CanBePicked(ATank* Tank) const 
{
	UE_LOG(LogTemp, Warning, TEXT("Currenthp: %i / StartingHP: %i"), Tank->CurrentHealth, Tank->StartingHealth);
	if ((Tank->CurrentHealth) >= (Tank->StartingHealth)) {
		return false;
	}
	else {
		return true;
	}
}

