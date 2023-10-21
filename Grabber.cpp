// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"



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
	FindPhysicsHandleComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewpointLocation, PlayerViewpointRotation);
	FVector LineTraceEnd = PlayerViewpointLocation + (PlayerViewpointRotation.Vector()*SearchScale);
	
	//If the physics handle is attached
	//Move the object we are holding every tick
	if(PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}

	
	
	// ...
}

void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(PhysicsHandle)
	{
		//Physics Handle Found
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing Physics Handle Component"));
	}
}
void UGrabber::ActionGrab()
{
	//LineTrace and see if we reach any actors with physics body collision channel set
	GetFirstPhysicsbodyInReach();
	
	//If we hit something, attach a physics handle
	//Do attach physics handle
	auto HitResult = GetFirstPhysicsbodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto HasActorHit = HitResult.GetActor();

	if(HasActorHit)
	{
		PhysicsHandle->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true);
		auto ObjectMaterial = ComponentToGrab->GetMaterial(0);
		auto DynamicMaterial = ComponentToGrab->CreateDynamicMaterialInstance(0, ObjectMaterial);
		DynamicMaterial->SetScalarParameterValue("HighLight", 5.0f);
		ComponentToGrab->SetMaterial(0, DynamicMaterial);
		UE_LOG(LogTemp, Warning, TEXT("Material Highlighted"));
	}
}
void UGrabber::ActionRelease()
{
	if(PhysicsHandle->GrabbedComponent)
	{
		//Do release physics handle
		UE_LOG(LogTemp, Warning, TEXT("Grab Released"));
		auto ObjectMaterial = PhysicsHandle->GrabbedComponent->GetMaterial(0);
		auto DynamicMaterial = PhysicsHandle->GrabbedComponent->CreateDynamicMaterialInstance(0, ObjectMaterial);
		DynamicMaterial->SetScalarParameterValue("Highlight", 0.0f);
		PhysicsHandle->ReleaseComponent();
	}
}
const FHitResult UGrabber::GetFirstPhysicsbodyInReach()
	{
		UE_LOG(LogTemp, Warning, TEXT("Grab Pressed"));
		//Get Player Location and Rotation
		FVector PlayerViewpointLocation;
		FRotator PlayerViewpointRotation;
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewpointLocation, PlayerViewpointRotation);
		FVector LineTraceEnd = PlayerViewpointLocation + (PlayerViewpointRotation.Vector()*SearchScale);

		//Line trace object
		FHitResult TargetHit;
		GetWorld()->LineTraceSingleByObjectType(TargetHit, PlayerViewpointLocation, LineTraceEnd, FCollisionObjectQueryParams(ECC_PhysicsBody));
	
		//Draw Debug line for visualize hit
		DrawDebugLine(GetWorld(), PlayerViewpointLocation, LineTraceEnd, FColor::Red, false, 0.f, 0.f, 10.f);

		if(TargetHit.GetActor())
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit actor is : %s"), *(TargetHit.GetActor()->GetName()));
		}
	
		//Return last hit actor
		return TargetHit;
	}

