// Copyright Benedikt Kirchmeier 2018

#include "Grabber.h"
#include <Engine/World.h>
#include "DrawDebugHelpers.h"
#include "Components/PrimitiveComponent.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandle();
	SetupInputComponent();
}

// Attaches a Physics Handle to the Object found by GetFirstPhysicsBodyInReach()
void UGrabber::Grab()
{
	/// line trace and reach any actors with physics body collision channel set
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	/// if we hit something then attach a physics handle
	if (ActorHit)
	{
		if (!PhysicsHandle) { return; };
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			GetOwner()->GetActorRotation()
		);
	}
}

// Releases the Object grabbed
void UGrabber::GrabRelease()
{
	if (!PhysicsHandle) { return; };
	PhysicsHandle->ReleaseComponent();
}

// Shoot a Line Trace to get the first Object in reach of the owner with a Physics Body
const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	/// Get the player reach end
	FVector LineTraceEnd = GetLineTracePoint(false);
	/// Setup query parameters
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	/// Raycasting out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetLineTracePoint(true),
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);
	return Hit;
}

// Find attached physics handle component
void UGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing Physics Handle"), *GetOwner()->GetName());
	}
}

// Setup attached input component
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::GrabRelease);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing Input Component"), *GetOwner()->GetName());
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (!PhysicsHandle) { return; };
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PhysicsHandle->GrabbedComponent)
	{
		/// move the object that were holding
		PhysicsHandle->SetTargetLocation(GetLineTracePoint(false));
	}
}

// Gets the end point of the reach trace when param is false and the player viewpoint location if true
FVector UGrabber::GetLineTracePoint(bool bGetStart)
{
	APlayerController* Player = GetWorld()->GetFirstPlayerController();
	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;
	Player->GetPlayerViewPoint(
		OUT PlayerViewpointLocation,
		OUT PlayerViewpointRotation
	);
	if (bGetStart == false)
	{
		return PlayerViewpointLocation + PlayerViewpointRotation.Vector()*Reach;
	}
	else
	{
		return PlayerViewpointLocation;
	}
}
