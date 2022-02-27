// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Bullet_man.h"
#include "Components/BoxComponent.h"
#include "Character_Movement.generated.h"

UCLASS()
class PEN_API ACharacter_Movement : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacter_Movement();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	
	//The gun
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Mesh)
		class USkeletalMeshComponent* shit;

	//The Camera
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Mesh)
		class UCameraComponent* cam;
	
	//The SpringArmComponent which allows for additional functions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USpringArmComponent* arm;

	//The hands of the player
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Mesh)
		class USkeletalMeshComponent* hands;

	//From where the bullet is suppposed to go.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USceneComponent* Bullet_go;
	
	//Playing the sound
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* Sound_Play;

	//The bullet class 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
		TSubclassOf<ABullet_man> bullet_class_mesh;
	
	
	//To take damage
	UPROPERTY(EditAnywhere , BlueprintReadWrite)
		class UBoxComponent* Collsion_component;


	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult);



	void tpp();
	
	//The Movement functions
	void Forward_Back(float value);

	void Left_Right(float value);

	void Horizontal_View(float value);

	void Vertical_View(float value);

	bool fpp;

	void fire();

	//The start for Bullet
	FVector start;

	//The Rotation
	FRotator axis_of_the_worlds;

	FActorSpawnParameters spawn;
	
	UPROPERTY(EditAnywhere , BlueprintReadOnly)
		float health = 100.0f;
};
