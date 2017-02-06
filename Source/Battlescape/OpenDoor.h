// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();

	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		
private:
	AActor* Owner;
	float CloseDelay = 0.5f;

	UPROPERTY(VisibleAnywhere)
		float LastOpened;

	UPROPERTY(VisibleAnywhere)
		float OpenAngle = 20.f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate;

	AActor* OpenActor;

};
