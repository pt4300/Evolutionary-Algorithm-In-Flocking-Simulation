// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelGenerator.h"


// Sets default values
ALevelGenerator::ALevelGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelGenerator::BeginPlay()
{
	Super::BeginPlay();


	
	initialisation();
	for(auto predator:predatorArray)
	{
		predator->targetArray = boidsArray;
		predator->selectTarget(predator->targetArray);

	}
	
}

// Called every frame
void ALevelGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	for(auto boid:boidsArray )
	{
		FVector acceleration = FVector(0, 0, 0);

		FVector align = boid->alignWithOther(boidsArray);
		FVector center = boid->flyingToCentre(boidsArray);
		FVector separation = boid->avoidOthers(boidsArray);
		FVector avoidAsteroid = boid->avoidAsteroid(AsteroidsArray);
		FVector avoidPredator = boid->avoidPredator(predatorArray);
		if (boid->deathMethod == 0) {
			for (auto asteroid : AsteroidsArray)
			{
				float distance = FVector::Dist(boid->GetActorLocation(), asteroid->GetActorLocation());
				{
					if (distance < 10)
					{
						
						boid->SetActorLocation(FVector(10000, 10000, 10000));
						boid->SetActorTickEnabled(false);
						boid->deathMethod = 1;
						UE_LOG(LogTemp, Warning, TEXT("Killed by asteroid"));


					}
				}
			}
			// only survived boid need move
			acceleration += align * boid->alignmentFactor;
			acceleration += center *boid->centreFactor;
			acceleration += separation * boid->separationFactor;
			acceleration += avoidAsteroid;
			acceleration += avoidPredator *10;
			FVector distanceToMigratePoint = migratePoint->GetActorLocation() - boid->position;
			//distanceToMigratePoint = distanceToMigratePoint.GetClampedToMaxSize(100);
			acceleration += distanceToMigratePoint;

			boid->velocity += acceleration;
			acceleration = acceleration * 0;

			//if(boid->velocity.Size()>100)
			//{
			//	boid->velocity = boid->velocity.GetClampedToMaxSize(100);
			//}

		}
		if(boid->deathMethod !=0)
		{
			if(!deadArray.Contains(boid))
			{
				deadArray.Add(boid);
				UE_LOG(LogTemp, Warning, TEXT("Killed by predator: %i"), deadArray.Num());
			}


		}


	}



	testCounter++;

	if(deadArray.Num()>=80)
	{

		UE_LOG(LogTemp, Warning, TEXT("This round Last: %i"),testCounter);
		testCounter = 0;
		calculateFitness();
		for(int i =0;i<50;i++)
		{
			ABoids* parent1 = parentSelection();
			ABoids* parent2 = parentSelection();
			if(parent1==NULL || parent2==NULL)
			{
				UE_LOG(LogTemp, Warning, TEXT("bugs trigger!!!"));
			}
			TArray<float> newDNA1 = parent1->crossOver(parent2, 2);
			TArray<float> newDNA2 = parent2->crossOver(parent1, 2);

			DNAarray.Add(newDNA1);
			DNAarray.Add(newDNA2);
			
			
		}
		for (auto boid : boidsArray)
		{
			boid->Destroy();
		}
		boidsArray.Empty();

		survivalSelection();
		 //need reassign target for predator
		for(auto predator:predatorArray)
		{
			predator->targetArray = boidsArray;
			predator->selectTarget(predator->targetArray);
		}
	}

	
	int64 currentTime = FDateTime::UtcNow().ToUnixTimestamp();
	if(currentTime > targetTime)
	{
		targetTime = FDateTime::UtcNow().ToUnixTimestamp() + timer;
		int RandXPos = 0;
		int RandYPos = 0;
		int RandZPos = 0;



		RandXPos = FMath::RandRange(-3000, 3000);
		RandYPos = FMath::RandRange(-3000, 3000);
		RandZPos = FMath::RandRange(-3000, 3000);

		FVector Position(RandXPos, RandYPos, RandZPos);
		
		migratePoint->SetActorLocation(Position);
		
	}

	

}


void ALevelGenerator::initialisation()
{
	UWorld* World = GetWorld();
	if (BoidActorBlueprint)
	{
		for (int i = 0; i < 100; i++)
		{
			int RandXPos = 0;
			int RandYPos = 0;
			int RandZPos = 0;



			RandXPos = FMath::RandRange(-3000, 3000);
			RandYPos = FMath::RandRange(-3000, 3000);
			RandZPos = FMath::RandRange(-3000, 3000);


			FVector Position(RandXPos, RandYPos, RandZPos);
			ABoids* NewBoids = World->SpawnActor<ABoids>(BoidActorBlueprint, Position, FRotator::ZeroRotator);
			NewBoids->speed = FMath::RandRange(200, 380);
			NewBoids->turnRate = FMath::RandRange(100, 400);

			NewBoids->avoidanceDistance = FMath::RandRange(100, 1000);
			NewBoids->perceptionRadius = FMath::RandRange(500, 3000);
			boidsArray.Add(NewBoids);
			

			
			
		}
	}
	if(MigratoryUrgeBP)
	{
		int RandXPos = 0;
		int RandYPos = 0;
		int RandZPos = 0;



		RandXPos = FMath::RandRange(-3000, 3000);
		RandYPos = FMath::RandRange(-3000, 3000);
		RandZPos = FMath::RandRange(-3000, 3000);

		FVector Position(RandXPos, RandYPos, RandZPos);
		migratePoint = World->SpawnActor<AMigratoryUrge>(MigratoryUrgeBP, Position, FRotator::ZeroRotator);
		targetTime = FDateTime::UtcNow().ToUnixTimestamp() + timer;
	}

	for (int i = 0; i < 20; i++)
	{
		int RandXPos = 0;
		int RandYPos = 0;
		int RandZPos = 0;



		RandXPos = FMath::RandRange(-3000, 3000);
		RandYPos = FMath::RandRange(-3000, 3000);
		RandZPos = FMath::RandRange(-3000, 3000);


		FVector Position(RandXPos, RandYPos, RandZPos);
		AAsteroid* newAsteroid = World->SpawnActor<AAsteroid>(Asteroids, Position, FRotator::ZeroRotator);
		AsteroidsArray.Add(newAsteroid);



	}
	if(PredatorBP)
	{
		for (int i = 0; i < 4; i++)
		{
			int RandXPos = 0;
			int RandYPos = 0;
			int RandZPos = 0;



			RandXPos = FMath::RandRange(-3000, 3000);
			RandYPos = FMath::RandRange(-3000, 3000);
			RandZPos = FMath::RandRange(-3000, 3000);


			FVector Position(RandXPos, RandYPos, RandZPos);
			APredator* newPredator = World->SpawnActor<APredator>(PredatorBP, Position, FRotator::ZeroRotator);
			newPredator->speed = FMath::RandRange(200, 400);
			predatorArray.Add(newPredator);
			



		}
	}


	
}


void ALevelGenerator::calculateFitness()
{
	for(auto boid : boidsArray)
	{
		if(boid->deathMethod == 1)
		{
			boid->survivalCounter = boid->survivalCounter * 0.75;
		}
		else if (boid->deathMethod == 2)
		{
			boid->survivalCounter = boid->survivalCounter * 0.5;
		}
	}
}


ABoids* ALevelGenerator::parentSelection()
{
	// using roulette wheel selection
	float sumFitness = 0;
	int current = 0;
	ABoids* returnBoids = NULL;
	for (auto boid:boidsArray)
	{
		sumFitness += boid->survivalCounter;
	}
	float chance = FMath::RandRange(0.00, sumFitness);
	boidsArray.Sort([](ABoids& A, ABoids& B)
	{
		return B.survivalCounter > A.survivalCounter;
	});
	for (auto boid :boidsArray)
	{
		current += boid->survivalCounter;
		if (current > chance)
		{
			
			returnBoids = boid;
			return returnBoids;
		}
	}

	if(returnBoids == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("No parent selected!!!"));
	}
	return  returnBoids;
	
}


void ALevelGenerator::survivalSelection()
{
	UWorld* World = GetWorld();
	deadArray.Empty();
	if(BoidActorBlueprint)
	{

		
		for(auto DNA:DNAarray)
		{
			int RandXPos = 0;
			int RandYPos = 0;
			int RandZPos = 0;



			RandXPos = FMath::RandRange(-3000, 3000);
			RandYPos = FMath::RandRange(-3000, 3000);
			RandZPos = FMath::RandRange(-3000, 3000);


			FVector Position(RandXPos, RandYPos, RandZPos);
			ABoids* NewBoids = World->SpawnActor<ABoids>(BoidActorBlueprint, Position, FRotator::ZeroRotator);
			NewBoids->speed = DNA[0];
			NewBoids->turnRate = DNA[1];
			NewBoids->avoidanceDistance = DNA[2];
			NewBoids->perceptionRadius = DNA[3];
			boidsArray.Add(NewBoids);

		}
	}
	DNAarray.Empty();
	
}


