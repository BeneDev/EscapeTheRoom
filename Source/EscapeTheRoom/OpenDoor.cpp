// Copyright Benedikt Kirchmeier 2018

#include "OpenDoor.h"
#include <Gameframework/Actor.h>
#include <Engine/World.h>

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	//Get the owner
	Owner = GetOwner();
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing PressurePlate"), *Owner->GetName());
	}
}

// Get the mass of the actors on the trigger plate for the door, the file is on
float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;
	/// Find all the overlapping actors
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) { return 0.0f; };
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	/// Iterate through them counting up total mass
	for (const auto* Act : OverlappingActors)
	{
		TotalMass += Act->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// Poll the Trigger Volume
	// TODO make this not poll every tick, but based on an event
	if (GetTotalMassOfActorsOnPlate() >= TriggerMass)
	{
		OnOpenRequest.Broadcast();
	}
	else
	{
		OnCloseRequest.Broadcast();
	}
}

