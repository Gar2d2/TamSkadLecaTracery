// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletParent.h"
#include "Components/SphereComponent.h"

#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABulletParent::ABulletParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(15.0f);
	RootComponent = CollisionComponent;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 300.0f;
	ProjectileMovementComponent->MaxSpeed = 300.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;

}

// Called when the game starts or when spawned
void ABulletParent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABulletParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABulletParent::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}