// Fill out your copyright notice in the Description page of Project Settings.


#include "MigratoryUrge.h"

// Sets default values
AMigratoryUrge::AMigratoryUrge()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMigratoryUrge::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMigratoryUrge::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	position = GetActorLocation();

}

