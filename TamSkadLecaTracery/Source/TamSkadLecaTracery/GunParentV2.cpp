// Fill out your copyright notice in the Description page of Project Settings.


#include "GunParentV2.h"
#include "BulletParent.h"
#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"

AGunParentV2::AGunParentV2()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



}
void AGunParentV2::Fire(FTransform BulletSpawnTransform, UParticleSystem* MuzzleFlash, USceneComponent* AttachTo)
{
	if (!ensure(BulletClass))
	{
		return;
	}
	if (InMagAmmo > 0)
	{
		//auto Bullet = GetWorld()->SpawnActorDeferred<ABulletParent>(BulletClass,BulletSpawnTransform);
		auto Bullet = GetWorld()->SpawnActor<ABulletParent>(BulletClass,BulletSpawnTransform);   ///spawning bullet from template
		if (!Bullet) { return; }
		Bullet->SetLifeSpan(BulletLifeTime);
		Bullet->FireInDirection(BulletSpawnTransform.GetRotation().GetForwardVector(), Bullet->GetInitialBulletSpeed());
		//Bullet->FinishSpawning(BulletSpawnTransform);
		InMagAmmo--;
		if (MuzzleFlash && AttachTo)
		{
			UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, AttachTo, FName("Bullet"));  //spawning particle from template
		}
	}
	
}

void AGunParentV2::Reload()
{
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle,this, &AGunParentV2::FillMagFromAmmoLeft, ReloadTime, false);
}


inline FString AGunParentV2::GetAmmoLeft() const
{
	return FString::FromInt(InMagAmmo) + FString("/") + FString::FromInt(CarryOnAmmo);
}

void AGunParentV2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGunParentV2::FillMagFromAmmoLeft()
{
	if (!ensure(MagazineSize >= 0)) 
	{
		UE_LOG(LogTemp, Warning, TEXT("MagazineSize cannot be lower then 1 you idiot"));
		return;
	}

	if (CarryOnAmmo > 0) 
	{
		int AmmoDifference = InMagAmmo;//saving current ammo in mag value
		InMagAmmo += FMath::Clamp<int>(CarryOnAmmo, 0, MagazineSize - InMagAmmo);
		CarryOnAmmo -= InMagAmmo - AmmoDifference;
	}
	//UE_LOG(LogTemp, Warning, TEXT("Xd"));
}
