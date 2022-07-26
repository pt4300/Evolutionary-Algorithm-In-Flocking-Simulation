// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Boids.h"
#include "Asteroid.h"
#include "MigratoryUrge.h"
#include "Predator.h"
#include "LevelGenerator.generated.h"



UCLASS()
class FLOCKING_API ALevelGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Entities")
		TSubclassOf<AActor> BoidActorBlueprint;

	UPROPERTY(EditAnywhere, Category = "Entities")
		TSubclassOf<AActor> Asteroids;

	UPROPERTY(EditAnywhere, Category = "Entities")
		TSubclassOf<AActor> MigratoryUrgeBP;

	UPROPERTY(EditAnywhere, Category = "Entities")
		TSubclassOf<AActor> PredatorBP;

	void initialisation();
	void calculateFitness();
	ABoids* parentSelection();
	void crossOver();
	void mutation();
	void survivalSelection();

	TArray<ABoids*> boidsArray = TArray<ABoids*>();
	TArray<APredator*> predatorArray = TArray<APredator*>();
	TArray<AAsteroid*>AsteroidsArray = TArray<AAsteroid*>();
	TArray<ABoids*> deadArray = TArray<ABoids*>();

	TArray<TArray<float>> DNAarray;
	
	int survivedBoidCounter = 100;


	AMigratoryUrge* migratePoint;
	int64 targetTime;
	int64 timer = 30;


	int testCounter = 0;
	

};
