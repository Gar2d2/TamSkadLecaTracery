// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DefaultCH.generated.h"

class UCameraComponent;
class UAnimInstance;


UCLASS()
class TAMSKADLECATRACERY_API ADefaultCH : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADefaultCH();
	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetupVariables(UAnimInstance* Ref);
	UFUNCTION(BlueprintCallable, Category = "Setup")
	float CalculateMovementDirection() const; //calculates direction for ABP "Direction"
	UAnimInstance * ABPRef = nullptr;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
};
