// Copyright Benedikt Kirchmeier 2018

#include "Grabber.h"
#include <Engine/World.h>
#include "DrawDebugHelpers.h"
#include "Components/PrimitiveComponent.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandle();
	SetupInputComponent();
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("I'm grabbing now!"));
	/// line trace and reach any actors with physics body collision channel set
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	/// if we hit something then attach a physics handle
	if (ActorHit)
	{
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			GetOwner()->GetActorRotation()
		);
	}
}

void UGrabber::GrabRelease()
{
	UE_LOG(LogTemp, Warning, TEXT("I'm releasing the object again!"));
	PhysicsHandle->ReleaseComponent();
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	/// Get the player view point
	APlayerController* Player = GetWorld()->GetFirstPlayerController();
	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;
	Player->GetPlayerViewPoint(
		OUT PlayerViewpointLocation,
		OUT PlayerViewpointRotation
	);
	FVector LineTraceEnd = PlayerViewpointLocation + PlayerViewpointRotation.Vector()*Reach;
	/// Setup query parameters
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	/// Raycasting out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewpointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);
	/// See what we hit
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is in Front of me!"), *ActorHit->GetName());
	}
	return Hit;
}
// Find attached physics handle component
void UGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		/// Physics Handle found
	}
	else
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
		UE_LOG(LogTemp, Warning, TEXT("Input Component found"))
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
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle->GrabbedComponent)
	{
		APlayerController* Player = GetWorld()->GetFirstPlayerController();
		FVector PlayerViewpointLocation;
		FRotator PlayerViewpointRotation;
		Player->GetPlayerViewPoint(
			OUT PlayerViewpointLocation,
			OUT PlayerViewpointRotation
		);
		FVector LineTraceEnd = PlayerViewpointLocation + PlayerViewpointRotation.Vector()*Reach;
		/// move the object that were holding
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
}

