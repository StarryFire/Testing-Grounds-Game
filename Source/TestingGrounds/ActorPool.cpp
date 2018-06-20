// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorPool.h"


// Sets default values for this component's properties
UActorPool::UActorPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

AActor* UActorPool::Checkout()
{
	if (ActorPool.Num() == 0)
		return nullptr;
	else
	{
		auto Actor = ActorPool.Pop();
		UE_LOG(LogTemp, Warning, TEXT("Checkedout %s"), *Actor->GetName());
		return Actor;
	}
}

void UActorPool::Return(AActor* Actor)
{
	if (Actor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Returned %s"), *Actor->GetName());
		ActorPool.Push(Actor);
	}
}

void UActorPool::Add(AActor* Actor)
{
	if (Actor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Added %s"), *Actor->GetName());
		ActorPool.Push(Actor);
	}
}
