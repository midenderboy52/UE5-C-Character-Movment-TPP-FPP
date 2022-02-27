// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Bullet_man.h"
#include "Components/BoxComponent.h"
#include "PRO_IT_IS.generated.h"

UCLASS()
class PEN_API APRO_IT_IS : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APRO_IT_IS();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	//The Muzzle of the gun
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USceneComponent* muz;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Mesh)
		class USkeletalMeshComponent* shit;

	//The Camera
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Mesh)
		class UCameraComponent* cam;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USpringArmComponent* lol;


	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Mesh)
		class USkeletalMeshComponent* sesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USceneComponent* pen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* hell;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
		TSubclassOf<ABullet_man> bullf;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
		class UBoxComponent* liz;


	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult);



	void lpp();

	void Forward_Back(float value);

	void Left_Right(float value);

	void Horizontal_View(float value);

	void Vertical_View(float value);

	bool fpp;

	void fire();

	//When Object hit.
	FHitResult lens;

	//IDK
	FCollisionQueryParams ken;

	//The start for LineTrace
	FVector start;

	//The end for LineTrace
	FRotator axis_of_the_worlds;

	FActorSpawnParameters spawn;

	void sops();
	
	UPROPERTY(EditAnywhere , BlueprintReadOnly)
		float health = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float health_for_gui = health / 100.0f;

};