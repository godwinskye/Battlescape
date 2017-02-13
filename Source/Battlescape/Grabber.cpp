// Fill out your copyright notice in the Description page of Project Settings.

#include "Battlescape.h"
#include "Grabber.h"

#define ALTER

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
	
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	FVector PlayerLocation;
	FRotator PlayerCameraRotator;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(ALTER PlayerLocation, ALTER PlayerCameraRotator);

	//Debug purposes
	//UE_LOG(LogTemp, Warning, TEXT("Now at (%s, %s)"), *PlayerLocation.ToString(), *PlayerCameraRotator.ToString());
	FVector PlayerReach = PlayerLocation + PlayerCameraRotator.Vector() * Reach;
	DrawDebugLine(GetWorld(), PlayerLocation, PlayerReach, FColor(255, 0, 0), false, 0.f, 0.f, 10.f);

	//Ray-casting variables
	FHitResult HitObject;
	FCollisionObjectQueryParams HitTargets(ECollisionChannel::ECC_PhysicsBody);
	FCollisionQueryParams HitParams(FName(TEXT("")), false, GetOwner());
	//Ray-casting method
	GetWorld()->LineTraceSingleByObjectType(ALTER HitObject, PlayerLocation, PlayerReach, HitTargets, HitParams);

	//Debug purposes: hit object
	AActor* HitSuccess = HitObject.GetActor();
	if (HitSuccess) {
		UE_LOG(LogTemp, Warning, TEXT("%s Hit!"), *(HitSuccess->GetName()));
	}
}

