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


//Look for InputComponent and binds grab action

void UGrabber::setupInput()
{
	m_InputHandle = GetOwner()->FindComponentByClass<UInputComponent>();
	if (m_InputHandle)
	{
		m_InputHandle->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		m_InputHandle->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else { UE_LOG(LogTemp, Error, TEXT("INPUTHANDLE WAS NOT FOUND IN %s"), *GetOwner()->GetName()); }
}

//Look for Physics Handle
void UGrabber::setupPhysics()
{
	m_PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (m_PhysicsHandle == nullptr){ UE_LOG(LogTemp, Error, TEXT("PHYSICS HANDLE WAS NOT FOUND IN %s"), *GetOwner()->GetName()); }
}

FVector UGrabber::getPlayerLocation() const
{
	APlayerController* player = GetWorld()->GetFirstPlayerController();
	FVector playerLocation;
	FRotator playerRotation;
	player->GetPlayerViewPoint(OUT playerLocation, OUT playerRotation);
	return playerLocation;
}

FVector UGrabber::GetReachEndPos() const
{
	APlayerController* player = GetWorld()->GetFirstPlayerController();
	FVector playerLocation;
	FRotator playerRotation;
	player->GetPlayerViewPoint(OUT playerLocation, OUT playerRotation);
	return playerLocation + playerRotation.Vector()*m_Reach;
}

void UGrabber::SetupComponents()
{

	setupPhysics();

	setupInput();
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	// ...
	SetupComponents();
}


FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	/// Get player Viewpoint
	
	FVector playerLocation = getPlayerLocation();
	///DebugLine
	FVector reachEndPos = GetReachEndPos();
	///Ray cast to reach distance
	FHitResult lineHit;
	GetWorld()->LineTraceSingleByObjectType(OUT lineHit, playerLocation, reachEndPos,
		FCollisionObjectQueryParams(ECC_PhysicsBody),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner()));
	return lineHit;
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector reachEndPos = GetReachEndPos();
	///if physics handle, 
	if (m_PhysicsHandle->GrabbedComponent)
	{
		m_PhysicsHandle->SetTargetLocation(reachEndPos);
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Error, TEXT("Grab pressed"));

	/// reach actors with physics collision
	///line trace
	auto lineHit = GetFirstPhysicsBodyInReach();
	auto hitActor = lineHit.GetActor();
	if (hitActor)
	{
		/// attach physics handle
		auto hitComponent = lineHit.GetComponent();
		m_PhysicsHandle->GrabComponent(hitComponent, NAME_None, hitComponent->GetOwner()->GetActorLocation(), true);
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Error, TEXT("Grab released"));

	///release physics handle

	if (m_PhysicsHandle->GrabbedComponent)
	{
		m_PhysicsHandle->ReleaseComponent();
	}
}

