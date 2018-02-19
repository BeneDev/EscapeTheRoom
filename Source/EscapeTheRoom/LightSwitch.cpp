// Copyright Benedikt Kirchmeier 2018

#include "LightSwitch.h"


// Sets default values for this component's properties
ULightSwitch::ULightSwitch()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULightSwitch::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();

	if (PressurePlate == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing PressurePLate"), *Owner->GetName())
	}
}


// Called every frame
void ULightSwitch::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PressurePlate == nullptr) { return; }
	if (PressurePlate->IsOverlappingActor(GetWorld()->GetFirstPlayerController()))
	{
		OnTurnOn.Broadcast();
	}
	else
	{
		OnTurnOff.Broadcast();
	}
}
