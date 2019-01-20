// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

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
	FString objectName = GetOwner()->GetName();
	FString objectPos = GetOwner()->GetTransform().GetLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s is at position %s"), *objectName, *objectPos);
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	// Get player Viewpoint

	APlayerController* player = GetWorld()->GetFirstPlayerController();
	FVector location;
	FRotator rotation;
	player->GetPlayerViewPoint(OUT location, OUT rotation);
	//Ray cast to reach distance
	UE_LOG(LogTemp, Warning, TEXT("location: %s, rotation: %s"), *location.ToString(), *rotation.ToString())

	//See what we hit


}

