// Copyright Benedikt Kirchmeier 2018

#include "OpenDoor.h"
#include <Gameframework/Actor.h>


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
	AActor* Owner = GetOwner();
	// Create a rotator
	FRotator TargetRotation = FRotator(0.f, -75.f, 0.f);
	// Set the door rotation
	Owner->SetActorRotation(TargetRotation);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

