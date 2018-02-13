// Copyright Benedikt Kirchmeier 2018

#include "Grabber.h"
#include <Engine/World.h>

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get the player view point this tick
	APlayerController* Player = GetWorld()->GetFirstPlayerController();
	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;
	Player->GetPlayerViewPoint(
		OUT PlayerViewpointLocation,
		OUT PlayerViewpointRotation
	);
	UE_LOG(LogTemp, Warning, TEXT("%s looking in %s"), *PlayerViewpointLocation.ToString(), *PlayerViewpointRotation.ToString());
	// Raycasting out to reach distance
	// See what we hit
}

