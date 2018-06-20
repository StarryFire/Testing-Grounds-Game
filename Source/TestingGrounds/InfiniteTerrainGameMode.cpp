// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteTerrainGameMode.h"
#include "EngineUtils.h"
#include "TestingGroundsHUD.h"
#include "Player/FirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "ActorPool.h"


void AInfiniteTerrainGameMode::PopulateBoundsVolumePool()
{
	auto Iter = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	while (Iter)
	{
		NavMeshBoundsVolumePool->Add(*Iter);
		++Iter;
	}
}

UActorPool* AInfiniteTerrainGameMode::GetNavMeshBoundsVolumePool()
{
	return NavMeshBoundsVolumePool;
}

void AInfiniteTerrainGameMode::BeginPlay()
{
	Super::BeginPlay();
}

AInfiniteTerrainGameMode::AInfiniteTerrainGameMode() : Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Dynamic/Character/Behaviour/BP_Character"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATestingGroundsHUD::StaticClass();

	NavMeshBoundsVolumePool = CreateDefaultSubobject<UActorPool>(FName("NavMeshBoundsVolumePool"));
}



