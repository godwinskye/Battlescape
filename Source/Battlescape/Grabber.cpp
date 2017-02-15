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
	if (!PhysHandle || !InputHandle) {
		return;
	}

	if (PhysHandle->GrabbedComponent) {
		PhysHandle->SetTargetLocation(LineTrace().PlayerReach);
	}
}

UGrabber::LineTraceVectors UGrabber::LineTrace() {
	FVector PlayerLocation;
	FRotator PlayerCameraRotator;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(ALTER PlayerLocation, ALTER PlayerCameraRotator);

	FVector PlayerReach = PlayerLocation + PlayerCameraRotator.Vector() * Reach;

	return LineTraceVectors(PlayerLocation, PlayerReach);
}

void UGrabber::FindPhysComponent() {
	PhysHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysHandle) {
		UE_LOG(LogTemp, Error, TEXT("%s does not have a physics handle!"), *(GetOwner()->GetName()));
	}
}

void UGrabber::AttachInputComponent() {
	InputHandle = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputHandle) {
		InputHandle->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputHandle->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s does not have an input component!"), *(GetOwner()->GetName()));
	}
}

void UGrabber::Grab() {
	FHitResult HitObject = RayCastForObject();
	AActor* HitObjectPrescence = HitObject.GetActor();
	if (HitObjectPrescence) {
		PhysHandle->GrabComponent(
			HitObject.GetComponent(), 
			NAME_None, 
			HitObject.GetComponent()->GetOwner()->GetActorLocation(), 
			true
		);
	}
}

void UGrabber::Release() {
	if (!PhysHandle) {
		return;
	}
	PhysHandle->ReleaseComponent();
}

FHitResult UGrabber::RayCastForObject() {
	LineTraceVectors TraceResult = LineTrace();

	//Ray-casting objects
	FHitResult HitObject;
	FCollisionObjectQueryParams HitTargets(ECollisionChannel::ECC_PhysicsBody);
	FCollisionQueryParams HitParams(FName(TEXT("")), false, GetOwner());

	//Ray-casting method
	GetWorld()->LineTraceSingleByObjectType(
		ALTER HitObject, 
		TraceResult.PlayerLocation, 
		TraceResult.PlayerReach, 
		HitTargets, 
		HitParams
	);

	return HitObject;
}
