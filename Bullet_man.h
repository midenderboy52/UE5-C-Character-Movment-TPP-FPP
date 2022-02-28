// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet_man.generated.h"

UCLASS()
class PEN_API ABullet_man : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's propertiess
	ABullet_man();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Projectile)
		class USphereComponent* bully;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UProjectileMovementComponent* move_bully;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
};
