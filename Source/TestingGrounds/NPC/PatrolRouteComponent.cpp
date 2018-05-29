// Fill out your copyright notice in the Description page of Project Settings.

#include "PatrolRouteComponent.h"

TArray<AActor*> UPatrolRouteComponent::getPatrolPoints() const
{
	return PatrolPoints;
}

