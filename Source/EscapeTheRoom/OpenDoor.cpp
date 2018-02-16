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
}

// Open the door the file is on
void UOpenDoor::OpenDoor()
{
	Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
	bIsOpen = true;
}

// Close the door the file is on
void UOpenDoor::CloseDoor()
{
	Owner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
	bIsOpen = false;
}

// Get the mass of the actors on the trigger plate for the door, the file is on
float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;
	/// Find all the overlapping actors
	TArray<AActor*> OverlappingActors;
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
	if (GetTotalMassOfActorsOnPlate() >= TriggerMass)
	{
		OpenDoor();
	}
	else if(bIsOpen)
	{
		CloseDoor();
	}
}

