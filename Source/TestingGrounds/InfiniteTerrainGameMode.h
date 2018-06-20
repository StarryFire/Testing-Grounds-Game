// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InfiniteTerrainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGGROUNDS_API AInfiniteTerrainGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	class UActorPool* NavMeshBoundsVolumePool;

public:
	virtual void BeginPlay() override;
	
	AInfiniteTerrainGameMode();

	UFUNCTION(BlueprintCallable)
	void PopulateBoundsVolumePool();

	UFUNCTION(BlueprintCallable)
	class UActorPool* GetNavMeshBoundsVolumePool();
};
