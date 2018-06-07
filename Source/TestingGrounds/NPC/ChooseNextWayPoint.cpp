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
	auto index = blackBoardComp->GetValueAsInt(NextPatrolPointIndex.SelectedKeyName);
	auto patrolGuardController = OwnerComp.GetAIOwner();
	auto patrolRouteComponent = patrolGuardController->GetPawn()->FindComponentByClass<UPatrolRouteComponent>();

	if (ensure(patrolRouteComponent != NULL))
	{
		auto PatrolPoints = patrolRouteComponent->getPatrolPoints();
		if ( PatrolPoints.Num() > 0 )
		{
			blackBoardComp->SetValueAsObject(PatrolPoint.SelectedKeyName, PatrolPoints[index]);
			index = (index + 1) % PatrolPoints.Num();
			blackBoardComp->SetValueAsInt(NextPatrolPointIndex.SelectedKeyName, index);
		}
	}
	
	//UE_LOG(LogTemp, Warning, TEXT("nextWayPointIndex : %d"), index);
	return EBTNodeResult::Succeeded;
}




