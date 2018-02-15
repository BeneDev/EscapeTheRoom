// Copyright Benedikt Kirchmeier 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPETHEROOM_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// How far the player can reach from his central point
	UPROPERTY(EditAnywhere)
	float Reach = 50.0f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;
	
	// Find attached physics handle component
	void FindPhysicsHandle();
	// Setup attached input component
	void SetupInputComponent();

	// Raycast and grab whats in reach
	void Grab();
	// Release the object which has been grabbed
	void GrabRelease();
	// return the first physics body actor in reach
	const FHitResult GetFirstPhysicsBodyInReach();
};
