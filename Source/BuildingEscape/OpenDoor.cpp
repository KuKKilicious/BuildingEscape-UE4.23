// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "BuildingEscape.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"

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
	Owner = GetOwner();
	startYaw = GetOwner()->GetActorRotation().Yaw;
	if(!PressurePlate){UE_LOG(LogTemp, Warning, TEXT("missing pressure plate"));}
}

void UOpenDoor::OpenDoor()
{
	OnOpenRequest.Broadcast();
	
}

void UOpenDoor::CloseDoor()
{
	OnCloseRequest.Broadcast();
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float totalMass = 0.f;
	TArray<AActor*> overlaps;
	if(!PressurePlate){return 0.f;}
	
	PressurePlate->GetOverlappingActors(OUT overlaps);
	

	for (const auto& overlappingActor : overlaps)
	{
		totalMass += overlappingActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("on plate %s"), *overlappingActor->GetName());
	}
	return totalMass;
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//If the ActorThatOpens is in the volume
	if (GetTotalMassOfActorsOnPlate() >= m_MassThreshold) {

		OpenDoor();
		//LastDoorOpenedTime = GetWorld()->GetTimeSeconds();
	}else
	{
		CloseDoor();
	}

	//Check if its time to close the door
	/*if (GetWorld()->GetTimeSeconds() - LastDoorOpenedTime > DoorCloseDelay) {
		CloseDoor();
	}*/

}

