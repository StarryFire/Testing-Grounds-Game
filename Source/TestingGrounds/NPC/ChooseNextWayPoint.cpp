// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWayPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrolRouteComponent.h"

//Never use C++ class and then extend it in blueprint for a task!!!
//Always use C++ XOR Blueprint for making tasks in unreal
EBTNodeResult::Type UChooseNextWayPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	auto blackBoardComp = OwnerComp.GetBlackboardComponent();
	auto index = blackBoardComp->GetValueAsInt(nextWayPointIndex.SelectedKeyName);
	auto patrolGuardController = OwnerComp.GetAIOwner();
	auto patrolRouteComponent = patrolGuardController->GetPawn()->FindComponentByClass<UPatrolRouteComponent>();

	if (ensure(patrolRouteComponent != NULL))
	{
		auto patrolPoints = patrolRouteComponent->getPatrolPoints();
		blackBoardComp->SetValueAsObject(waypoint.SelectedKeyName, patrolPoints[index]);
		index = (index + 1) % patrolPoints.Num();
		blackBoardComp->SetValueAsInt(nextWayPointIndex.SelectedKeyName, index);
	}
	
	//UE_LOG(LogTemp, Warning, TEXT("nextWayPointIndex : %d"), index);
	return EBTNodeResult::Succeeded;
}




