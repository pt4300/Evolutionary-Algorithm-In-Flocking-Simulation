// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Boids.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Predator.generated.h"

class ABoids;
UCLASS()
class FLOCKING_API APredator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APredator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void selectTarget(TArray<ABoids*> boidList);
	TArray<ABoids*> targetArray = TArray<ABoids*>();

	ABoids* currentTarget;
	FVector targetLocation;
	int speed = 0;
	float tolerance = 100;

	int64 predatorTimer = 5;
	int64 predatorTargetTime;
};
