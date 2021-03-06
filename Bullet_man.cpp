// Fill out your copyright notice in the Description page of Project Settings.

#include "Bullet_man.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Character_Movement.h"

// Sets default values
ABullet_man::ABullet_man()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Should also be a parent class of a blueprint actor class, to configure locations and rotations of components. 

	bully = CreateDefaultSubobject<USphereComponent>(TEXT("bully"));
	bully->InitSphereRadius(5.0f);

	
	RootComponent = bully;

	move_bully = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("move_bully"));
	//Updated component basically means TheMovementCompoenent is now the attached with bully thingy.
	move_bully->UpdatedComponent = bully;
	move_bully->InitialSpeed = 20000.0f;
	move_bully->MaxSpeed = 20000.0f;
	move_bully->bRotationFollowsVelocity = true;
	move_bully->bShouldBounce = true;
	
	//If this bullet doesnt hit in 3 sec it gets destroyed
	InitialLifeSpan = 3.0f;
	

}

// Called when the game starts or when spawned
void ABullet_man::BeginPlay()
{
	Super::BeginPlay();
	bully->OnComponentBeginOverlap.AddDynamic(this, &ABullet_man::OnHit);
	
}

// Called every frame
void ABullet_man::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABullet_man::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit){
	//Do whatever wanted
}
