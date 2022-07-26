// Fill out your copyright notice in the Description page of Project Settings.


#include "Boids.h"

#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ABoids::ABoids()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABoids::BeginPlay()
{

	int randVelocityX = FMath::RandRange(-100, 100);
	int randVelocityY = FMath::RandRange(-100, 100);
	int randVelocityZ = FMath::RandRange(-100, 100);

	velocity = FVector(randVelocityX, randVelocityY, randVelocityZ);

	Super::BeginPlay();
	
}

// Called every frame
void ABoids::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	survivalCounter += 1;
	position = this->GetActorLocation();

	targetLocation = position + velocity;
	//if(targeted == 1)
	//{
	//	speed = speed * fleeBoost;
	//}

	SetActorLocation(FMath::VInterpConstantTo(position, targetLocation, DeltaTime, speed));
	
	avoidCollisionWall();
	





}

FVector ABoids::alignWithOther(TArray<ABoids*>& boidsList)
{

	FVector steering = FVector(0, 0, 0);
	int totalBoid = 0;

	for (auto other : boidsList)
	{
		
		float distance = FVector::Dist(other->GetActorLocation(), GetActorLocation());
		if(other != this && distance <perceptionRadius)
		{
			steering += other->velocity;
			totalBoid+=1;
			
		}
	}
	
	if(totalBoid >0)
	{
		steering = steering / totalBoid;
		//steering = steering - this->velocity;
		steering = steering.GetClampedToMaxSize(100);
		
	}

	
	return steering;
}






FVector ABoids::flyingToCentre(TArray<ABoids*>& boidsList)
{
	FVector centerVector = FVector(0, 0, 0);
	int totalBoids = 0;

	for (auto other:boidsList)
	{

		float distance = FVector::Dist(other->GetActorLocation(), GetActorLocation());
		 
		if (other != this && distance < perceptionRadius)
		{
			centerVector += other->position;
			totalBoids += 1;
			
		}
	}

	if(totalBoids >0)
	{
		centerVector = centerVector / totalBoids;
		centerVector = centerVector - this->position;
		centerPoint = centerVector;
		//centerVector = centerVector - this->velocity;
		//centerVector = centerVector.GetClampedToMaxSize(100);
	}
	return centerVector;
}


FVector ABoids::avoidOthers(TArray<ABoids*>& boidsList)
{
	FVector separationVector = FVector(0, 0, 0);
	int counter = 0;

	for (auto other : boidsList)
	{

		float distance = FVector::Dist(other->GetActorLocation(), GetActorLocation());

		if (other != this && distance < perceptionRadius)
		{
			FVector diff = this->position - other->position;
			diff = diff / (distance * distance);
			separationVector += diff;
			counter += 1;
			


		}
		
	}
	if(counter>0)
	{
		separationVector = separationVector / counter;
		//separationVector = separationVector - this->velocity;
		//separationVector = separationVector.GetClampedToMaxSize(100);
	}

	return separationVector;
	
}

FVector ABoids::avoidAsteroid(TArray<AAsteroid*>& asteroidList)
{
	FVector avoidVector = FVector(0, 0, 0);
	int totalBoids = 0;
	int minDistance = 30;

	for (auto other : asteroidList)
	{
		FVector asteroidLocation = other->GetActorLocation();
		float distance = FVector::Dist(other->GetActorLocation(), GetActorLocation());

		if (distance < avoidanceDistance)
		{
			avoidVector += this->position - FVector(other->GetActorLocation().X+turnRate, other->GetActorLocation().Y+turnRate, other->GetActorLocation().Z+turnRate);
			totalBoids += 1;

		}

	}

	return avoidVector;
}

FVector ABoids::avoidPredator(TArray<APredator*>& predatorList)
{
	FVector avoidanceVector = FVector(0, 0, 0);
	int counter = 0;

	for (auto other : predatorList)
	{

		float distance = FVector::Dist(other->GetActorLocation(), GetActorLocation());

		if (distance < avoidanceDistance)
		{
			FVector diff = this->position - other->GetActorLocation();
			
			//diff = diff / (distance * distance);
			avoidanceVector += this->position - FVector(other->GetActorLocation().X + turnRate, other->GetActorLocation().Y + turnRate, other->GetActorLocation().Z + turnRate);
			counter += 1;



		}

	}
	if (counter > 0)
	{
		//avoidanceVector = avoidanceVector / counter;
		//separationVector = separationVector - this->velocity;
	}

	return avoidanceVector;
}



void ABoids::avoidCollisionWall()
{

	if (GetActorLocation().Y < -3000)
	{
		velocity.Y = -velocity.Y;
		//SetActorLocation(FVector(0, 0, 0));
	}
	if (GetActorLocation().X < -3000)
	{
		//velocity.X += 200;

		velocity.X = -velocity.X;
	}
	if (GetActorLocation().Y > 3000)
	{
		//velocity.Y -= 200;
		velocity.Y = 0 - velocity.Y;

	}
	if (GetActorLocation().X > 3000)
	{
		//velocity.X -= 200;
		velocity.X = 0 - velocity.X;

		//SetActorLocation(FVector(2800, GetActorLocation().Y, GetActorLocation().Z));

	}

	if (GetActorLocation().Z > 3000)
	{
		velocity.Z = 0 -velocity.Z;

		//velocity.Z -= 200;
		//SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, 2800));

	}
	if (GetActorLocation().Z < -3000)
	{
		velocity.Z = 0 -velocity.Z;

		//velocity.Z += 200;
		//SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, -2800));

	}
}

TArray<float> ABoids::crossOver(ABoids* other,int middlePoint)
{
	//return the new boids DNA and spawn in level generator
	DNA.Add(speed); // speed is 0
	DNA.Add(turnRate); //turn rate is 1
	DNA.Add(avoidanceDistance); // force apply to avoidanceDistance is 2
	DNA.Add(perceptionRadius); // perception is 3

	other->DNA.Add(other->speed);
	other->DNA.Add(other->turnRate);

	other->DNA.Add(other->avoidanceDistance);
	other->DNA.Add(other->perceptionRadius);

	//10 percent chance of mutation
	bool isMutated = FMath::RandRange(1, 50) == 1 ? true : false;
	TArray<float>childDNA;

	for(int i=0; i<middlePoint; i++)
	{
		childDNA.Add(this->DNA[i]);
	}

	for (int i=middlePoint; i <= 3; i++)
	{
		childDNA.Add(other->DNA[i]);
	}
	if(isMutated)
	{
		// each time only one gene will be mutated 
		int mutatedGene = FMath::RandRange(0, 3);
		if(mutatedGene == 0)
		{
			childDNA[0] = FMath::RandRange(50, 300);
		}
		else if (mutatedGene == 1)
		{
			childDNA[1] = FMath::RandRange(10, 200);
		}
		else if (mutatedGene == 2)
		{
			childDNA[2] = FMath::RandRange(50, 100);
		}
		else if (mutatedGene == 3)
		{
			childDNA[3] = FMath::RandRange(500, 3000);
		}





		
		
	}
	return childDNA;
}

