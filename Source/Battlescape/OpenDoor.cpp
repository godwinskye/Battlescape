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
}

void UOpenDoor::OpenDoor() {
	Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}

void UOpenDoor::CloseDoor() {
	Owner->SetActorRotation(FRotator(0.f, 80.f, 0.f));
}

float UOpenDoor::GetTotalMassOnPressurePlate() {
	float TotalMass = 0.f;

	TArray<AActor*> OverlappingObjects;
	PressurePlate->GetOverlappingActors(OverlappingObjects);

	for (auto& Object : OverlappingObjects) {
		TotalMass += Object->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}

// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (GetTotalMassOnPressurePlate() >= MassToOpenDoor) {
		OpenDoor();
		LastOpened = GetWorld()->GetRealTimeSeconds();
	}
	if (GetWorld()->GetRealTimeSeconds() - LastOpened > CloseDelay) {
		CloseDoor();
	}
	// ...
}

