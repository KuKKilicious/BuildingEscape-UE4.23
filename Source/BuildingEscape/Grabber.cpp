// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"

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
	/// Get player Viewpoint
	APlayerController* player = GetWorld()->GetFirstPlayerController();
	FVector playerLocation;
	FRotator playerRotation;
	player->GetPlayerViewPoint(OUT playerLocation, OUT playerRotation);

	//UE_LOG(LogTemp, Warning, TEXT("location: %s, rotation: %s"), *playerLocation.ToString(), *playerRotation.ToString());

	///DebugLine
	FVector LineTraceEnd = playerLocation + playerRotation.Vector()*m_Reach;
	DrawDebugLine(GetWorld(), playerLocation, LineTraceEnd, FColor(255, 255, 0), false, 0.f, 0, 10.0f);
	///Ray cast to reach distance
	FHitResult lineHit;
	GetWorld()->LineTraceSingleByObjectType(OUT lineHit, playerLocation, LineTraceEnd,
		FCollisionObjectQueryParams(ECC_PhysicsBody),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner()));
	AActor* actorHit = lineHit.GetActor();
	if (actorHit) { 
		UE_LOG(LogTemp, Warning, TEXT("actor hit %s"), *actorHit->GetName());
	}
	//See what we hit  
}

