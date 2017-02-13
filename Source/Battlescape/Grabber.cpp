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
	FindPhysComponent();
	AttachInputComponent();
}

// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	RayCast();
}

void UGrabber::FindPhysComponent() {
	PhysHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysHandle) {
		// success
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s does not have a physics handle!"), *(GetOwner()->GetName()));
	}
}

void UGrabber::AttachInputComponent() {
	InputHandle = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputHandle) {
		UE_LOG(LogTemp, Warning, TEXT("%s has an input component!"), *(GetOwner()->GetName()));
		InputHandle->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputHandle->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s does not have an input component!"), *(GetOwner()->GetName()));
	}
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed!"));
}

void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Grab released!"));
}

void UGrabber::RayCast() {
	FVector PlayerLocation;
	FRotator PlayerCameraRotator;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(ALTER PlayerLocation, ALTER PlayerCameraRotator);

	FVector PlayerReach = PlayerLocation + PlayerCameraRotator.Vector() * Reach;

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
