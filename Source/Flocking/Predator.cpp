// Fill out your copyright notice in the Description page of Project Settings.


#include "Predator.h"

// Sets default values
APredator::APredator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APredator::BeginPlay()
{
	Super::BeginPlay();
	// setup initial 30s timer
	
	predatorTargetTime = FDateTime::UtcNow().ToUnixTimestamp() + 5;

}

// Called every frame
void APredator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(FDateTime::UtcNow().ToUnixTimestamp() > predatorTargetTime)
	{

			float distance = FVector::Dist(currentTarget->GetActorLocation(), this->GetActorLocation());
			if (distance < tolerance)
			{
				currentTarget->deathMethod = 2;
				currentTarget->SetActorLocation(FVector(10000, 10000, 10000));
				predatorTargetTime = FDateTime::UtcNow().ToUnixTimestamp() + predatorTimer;
				UE_LOG(LogTemp, Warning, TEXT("Killed by predator!!!"));
				selectTarget(targetArray);
			}
			else
			{
				FVector currentLocation = this->GetActorLocation();

				targetLocation = currentLocation + (currentTarget->GetActorLocation() - currentLocation);
				SetActorLocation(FMath::VInterpConstantTo(currentLocation, targetLocation, DeltaTime, speed));

			}

		if (currentTarget->deathMethod != 0)
		{
			// avoid currentTarget killed by other
			UE_LOG(LogTemp, Warning, TEXT("Invalid target!!!"));
			selectTarget(targetArray);
		}

	}


}
void APredator::selectTarget(TArray<ABoids*> boidList)
{
	float localMin = 9999999;

	for (auto boid : boidList)
	{
		if (boid->deathMethod == 0 && boid->targeted == 0)
		{
			float diff = FVector::Dist(boid->GetActorLocation(), this->GetActorLocation());
			if (diff < localMin)
			{
				currentTarget = boid;
				localMin = diff;
			}
		}

	}
	//avoid two predator choose same target
	currentTarget->targeted = 1;
	targetArray.Remove(currentTarget);
}
