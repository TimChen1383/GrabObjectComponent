// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UECPP_PRACTICE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Grab action
	UFUNCTION(BlueprintCallable)
	void ActionGrab();

	UFUNCTION(BlueprintCallable)
	void ActionRelease();

	UPROPERTY(EditAnywhere, Category="Grabber")
	float SearchScale = 1000.0f;

	
	UPROPERTY(EditAnywhere, Category="Grabber")
	class UMaterialInterface* NormalMaterial;

	UPROPERTY(EditAnywhere, Category="Grabber")
	class UMaterialInterface* HighLightMaterial;

	

private:
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	void FindPhysicsHandleComponent();

	//Return hit for fist physics body in reach
	const FHitResult GetFirstPhysicsbodyInReach();



		
};



//use line trace hit object to get the actor and the component I want to grab > line trace single by object 
//Use Physic Handle to grab object > grab component at location with rotation ( PrimitiveComponent, BoneName, GrabLocation, grabRotation))