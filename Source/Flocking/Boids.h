// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Asteroid.h"
#include "Predator.h"
#include "Boids.generated.h"
class APredator;
UCLASS()
class FLOCKING_API ABoids : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoids();

	FVector velocity;
	FVector position;
	FVector targetLocation;
	FVector centerPoint;


	int survivalCounter = 0;
	//0 means survived, 1 means died due to collision, 2 for predator kill
	int deathMethod = 0;
	
	float speed = 0;
	float turnRate = 10;
	float alignmentFactor = 1;
	float centreFactor =1;
	float separationFactor = 1;
	float perceptionRadius = 0;

	// this applies to sense danger, apply to both predator and wall
	float avoidanceDistance = 1;

	// this applies to boid when they detect predator, applies to speed
	float fleeBoost = 10;

	
	float maxForce = 80;
	int targeted = 0;

	TArray<float>DNA;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector avoidOthers(TArray<ABoids*>& boidsList);
	FVector flyingToCentre(TArray<ABoids*>& boidsList);
	FVector alignWithOther(TArray<ABoids*>& boidsList);
	FVector avoidAsteroid(TArray<AAsteroid*>&  asteroidList);
	FVector avoidPredator(TArray<APredator*>& predatorList);
	void avoidCollisionWall();
	TArray<float> crossOver(ABoids* other,int middlePoint);

	
};
