// Fill out your copyright notice in the Description page of Project Settings.

#include "Battlescape.h"
#include "OpenDoor.h"

#define ALTER

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
	if (!Owner) {
		UE_LOG(LogTemp, Error, TEXT("No owner for OpenDoor"));
	}
}

void UOpenDoor::OpenDoor() {
	if (!Owner) {
		return;
	}
	OpenRequest.Broadcast();
}

void UOpenDoor::CloseDoor() {
	if (!Owner) {
		return;
	}
	CloseRequest.Broadcast();
}

float UOpenDoor::GetTotalMassOnPressurePlate() {
	float TotalMass = 0.f;

	TArray<AActor*> OverlappingObjects;
	PressurePlate->GetOverlappingActors(ALTER OverlappingObjects);

	for (auto& Object : OverlappingObjects) {
		TotalMass += Object->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}

// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("%s is missing pressure plate"), *(Owner->GetName()));
		return;
	}

	if (GetTotalMassOnPressurePlate() >= MassToOpenDoor) {
		OpenDoor();
	}
	else {
		CloseDoor();
	}
	// ...
}

