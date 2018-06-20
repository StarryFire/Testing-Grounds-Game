// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"
#include "AI/Navigation/NavigationSystem.h"
#include "DrawDebugHelpers.h"
#include "ActorPool.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NavigationBoundsOffset = FVector(2000, 0, 0);
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	CastSphere(GetActorLocation(), 300);
	
}

void ATile::SetPool(UActorPool* InPool)
{
	NavMeshBoundsVolumePool = InPool;
	if( NavMeshBoundsVolumePool )
		PositionNavMeshBoundsVolume();
	else
		UE_LOG(LogTemp, Warning, TEXT("NavMeshBoundsVolumePool is NULL"));
}

void ATile::PositionNavMeshBoundsVolume()
{
	NavMeshBoundsVolume = NavMeshBoundsVolumePool->Checkout();
	if (NavMeshBoundsVolume)
	{
		NavMeshBoundsVolume->SetActorLocation(GetActorLocation() + NavigationBoundsOffset);
		GetWorld()->GetNavigationSystem()->Build();
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("NavMeshBoundsVolume is NULL"));
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::PlaceActor(TSubclassOf<AActor> Actor, FSpawnParameters SpawnParameters)
{
	TArray<FSpawnTransform> SpawnTransforms = GenerateSpawnTransforms(SpawnParameters);
	for (auto SpawnTransform : SpawnTransforms)
	{
		auto SpawnedActor = GetWorld()->SpawnActor<AActor>(Actor);
		SpawnedActor->SetActorRelativeLocation(SpawnTransform.Location);
		SpawnedActor->SetActorRelativeRotation(FRotator(0, SpawnTransform.Rotation, 0));
		SpawnedActor->SetActorRelativeScale3D(FVector(SpawnTransform.Scale));
		SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	}
}

void ATile::PlaceAIPawn(TSubclassOf<APawn> Pawn, FSpawnParameters SpawnParameters)
{
	TArray<FSpawnTransform> SpawnTransforms = GenerateSpawnTransforms(SpawnParameters);
	for (auto SpawnTransform : SpawnTransforms)
	{
		auto SpawnedPawn = GetWorld()->SpawnActor<APawn>(Pawn);
		SpawnedPawn->SetActorRelativeLocation(SpawnTransform.Location);
		SpawnedPawn->SetActorRelativeRotation(FRotator(0, SpawnTransform.Rotation, 0));
		SpawnedPawn->SetActorRelativeScale3D(FVector(SpawnTransform.Scale));
		SpawnedPawn->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));

		SpawnedPawn->SpawnDefaultController();
	}
}


TArray<FSpawnTransform> ATile::GenerateSpawnTransforms(FSpawnParameters SpawnParameters)
{
	TArray<FSpawnTransform> SpawnTransforms;
	int NumSpawn = FMath::RandRange(SpawnParameters.MinSpawn, SpawnParameters.MaxSpawn);
	for (int i = 0; i < NumSpawn; ++i)
	{
		FSpawnTransform SpawnTransform;
		SpawnTransform.Scale = FMath::RandRange(SpawnParameters.MinScale, SpawnParameters.MaxScale);
		bool bSuccessful = GetEmptySpawnPoint(SpawnTransform.Location, SpawnTransform.Scale*SpawnParameters.Radius);
		if (bSuccessful)
		{
			SpawnTransform.Rotation = FMath::RandRange(-180, 180);
			SpawnTransforms.Push(SpawnTransform);
		}
	}

	return SpawnTransforms;
}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	NavMeshBoundsVolumePool->Return(NavMeshBoundsVolume);
}

bool ATile::GetEmptySpawnPoint(FVector &SpawnPoint, float SpawnRadius)
{
	FVector Min(FVector(0, -2000, 0));
	FVector Max(FVector(4000, 2000, 0));
	FBox Box(Min, Max);

	const int MAX_ATTEMPTS = 10;
	for (int i = 0; i < MAX_ATTEMPTS; ++i)
	{
		SpawnPoint = FMath::RandPointInBox(Box);
		if (!CastSphere(GetActorLocation() + SpawnPoint, SpawnRadius))
			return true;
	}
	return false;
}

bool ATile::CastSphere(FVector Location, float Radius)
{
	FHitResult HitResult;
	
	bool bHasHit = GetWorld()->SweepSingleByChannel(
		HitResult, 
		Location,
		Location, 
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2, 
		FCollisionShape::MakeSphere(Radius)
	);


	//DrawDebugCapsule(GetWorld(), Location, 0, Radius, FQuat::Identity, bHasHit?FColor::Red:FColor::Green, true);

	return bHasHit;
}


