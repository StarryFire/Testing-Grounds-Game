// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"


/**
 * SpawnTransform
 */
USTRUCT()
struct FSpawnTransform			
{
	GENERATED_USTRUCT_BODY()

	FVector Location;
	float Rotation;
	float Scale;
};

/**
 * RandomSpawnParameters
 */
USTRUCT(BlueprintType)
struct FSpawnParameters
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite)
	int MinSpawn = 1;
	UPROPERTY(BlueprintReadWrite)
	int MaxSpawn = 1;
	UPROPERTY(BlueprintReadWrite)
	float Radius = 500;
	UPROPERTY(BlueprintReadWrite)
	float MinScale = 1;
	UPROPERTY(BlueprintReadWrite)
	float MaxScale = 1;
};



UCLASS()
class TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()

	bool GetEmptySpawnPoint(FVector &SpawnPoint, float SpawnRadius);
	bool CastSphere(FVector Location, float Radius);
	class UActorPool* NavMeshBoundsVolumePool;

	TArray<FSpawnTransform> GenerateSpawnTransforms(FSpawnParameters SpawnParameters);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UFUNCTION(BlueprintCallable)
	void SetPool(class UActorPool *InPool);

	void PositionNavMeshBoundsVolume();
	AActor* NavMeshBoundsVolume;


public:	
	// Sets default values for this actor's properties
	ATile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	FVector NavigationBoundsOffset;

	UFUNCTION(BlueprintCallable)
	void PlaceActor(TSubclassOf<AActor> Actor, FSpawnParameters SpawnParameters);

	UFUNCTION(BlueprintCallable)
		void PlaceAIPawn(TSubclassOf<APawn> Pawn, FSpawnParameters SpawnParameters);

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	
};
