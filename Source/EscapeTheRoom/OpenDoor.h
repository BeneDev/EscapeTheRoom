// Copyright Benedikt Kirchmeier 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Containers/Array.h"
#include "Components/PrimitiveComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPETHEROOM_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	float OpenAngle = -75.f;

	UPROPERTY(EditAnywhere)
	float TriggerMass = 20.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	AActor* Owner;

	bool bIsOpen = false;

	void OpenDoor();

	void CloseDoor();

	float GetTotalMassOfActorsOnPlate();
};
