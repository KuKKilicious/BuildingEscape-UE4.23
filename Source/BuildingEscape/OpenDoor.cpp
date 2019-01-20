// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"


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


	ActorThatOpens= GetWorld()->GetFirstPlayerController()->GetPawn();
	startYaw = GetOwner()->GetActorRotation().Yaw;
	
}

void UOpenDoor::OpenDoor()
{
	// Find the owning Actor
	AActor* Owner = GetOwner();
	//Create a Rotator
	FRotator newRotation = FRotator(0.0f, startYaw+ 80.0f, 0.0f);
	//Set Door Rotation
	Owner->SetActorRotation(newRotation);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// Poll Trigger Volume
	if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
		OpenDoor();

	}
	//If the ActorThatOpens is in the volume
}
