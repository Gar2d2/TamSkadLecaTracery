// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GameStateParent.generated.h"


/**
 * 
 */
UCLASS()
class TAMSKADLECATRACERY_API AGameStateParent : public AGameState
{
	GENERATED_BODY()
public:
	//sort player array by player score
	UFUNCTION(BlueprintCallable, Category = "Utility")
	TArray<APlayerState*> SortByScore(TArray<APlayerState* > ArrToSort);


	
};
