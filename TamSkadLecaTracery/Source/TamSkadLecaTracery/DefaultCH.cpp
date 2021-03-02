// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultCH.h"
#include "UE4ManACPP.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ADefaultCH::ADefaultCH()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	
	
}

// Called when the game starts or when spawned
void ADefaultCH::BeginPlay()
{
	Super::BeginPlay();
	//Weapon = GetWorld()->SpawnActor(StartingWeapon); //spawns Weapon that can be attached to PrimaryWeapon slot in CH
}

void ADefaultCH::SetupVariables(UAnimInstance* Ref)
{
	ABPRef = Ref;
}

float ADefaultCH::CalculateMovementDirection() const
{
	auto Rotation = GetControlRotation();
	auto Velocity = GetVelocity();
	
	
	return ABPRef->CalculateDirection(GetVelocity(), FRotator(0,Rotation.Yaw,0));
}


void ADefaultCH::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//if (!Weapon)
	//{
	//	
	//	UE_LOG(LogTemp, Warning, TEXT("nimo"));
	//		//UE_LOG(LogTemp, Warning, TEXT("Text, %d %f %s"), intVar, floatVar, *fstringVar);
	//}
	//if (Weapon)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("jest"));
	//}
	//
}

// Called to bind functionality to input
void ADefaultCH::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
//canBeSeenFrom method for Ai perception sight 
bool ADefaultCH::CanBeSeenFrom(const FVector& ObserverLocation, FVector& OutSeenLocation, int32& NumberOfLoSChecksPerformed, float& OutSightStrength, const AActor* IgnoreActor) const
{
	static const FName NAME_AILineOfSight = FName(TEXT("TestPawnLineOfSight"));
	FHitResult HitResult;
	auto sockets = GetMesh()->GetAllSocketNames();
	//Here we consider the NeckSocket as the 
	FVector socketLocation = GetMesh()->GetSocketLocation("head");

	const bool bHitSocket = GetWorld()->LineTraceSingleByObjectType(HitResult, ObserverLocation, socketLocation, FCollisionObjectQueryParams(ECC_TO_BITFIELD(ECC_WorldStatic) | ECC_TO_BITFIELD(ECC_WorldDynamic)), FCollisionQueryParams(NAME_AILineOfSight, true, IgnoreActor));
	NumberOfLoSChecksPerformed++;
	if (bHitSocket == false || (HitResult.Actor.IsValid() && HitResult.Actor->IsOwnedBy(this)))
	{
		OutSeenLocation = socketLocation;
		OutSightStrength = 1;
		return true;
	}
	const bool bHit = GetWorld()->LineTraceSingleByObjectType(HitResult, ObserverLocation, GetActorLocation(), FCollisionObjectQueryParams(ECC_TO_BITFIELD(ECC_WorldStatic) | ECC_TO_BITFIELD(ECC_WorldDynamic)), FCollisionQueryParams(NAME_AILineOfSight, true, IgnoreActor));
	NumberOfLoSChecksPerformed++;
	if (bHit == false || (HitResult.Actor.IsValid() && HitResult.Actor->IsOwnedBy(this)))
	{
		OutSeenLocation = GetActorLocation();
		OutSightStrength = 1;
		return true;
	}
	OutSightStrength = 0;
	return false;
}
