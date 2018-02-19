// Copyright Benedikt Kirchmeier 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Components/LightComponent.h"
#include "Components/PointLightComponent.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "LightSwitch.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLightEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPETHEROOM_API ULightSwitch : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULightSwitch();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	AActor* Owner;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	FLightEvent OnTurnOn;

	FLightEvent OnTurnOff;
	
};
