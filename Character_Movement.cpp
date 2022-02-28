// Fill out your copyright notice in the Description page of Project Settings.


#include "Character_Movement.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "Bullet_man.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"



// Sets default values
ACharacter_Movement::ACharacter_Movement()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Possesing this player, you have to select Player 0 in unreal engine.
	//Select tthis character after placing it in the level and click on it
	//A search bar should pop up right side about properties of the player
	//Search "Player" there should be an option
	
	AutoPossessPlayer = EAutoReceiveInput::Player0;


	//The first paramater is the fat and the second one is the height
	GetCapsuleComponent()->SetCapsuleSize(100, 150);
	
	//Set all the components location in blueprint class which inherits from it, instead of code that makes it easier.
	
	arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("arm"));
	arm->SetupAttachment(GetCapsuleComponent());
	arm->TargetArmLength = 0;

	arm->bEnableCameraLag = true;
	arm->CameraLagSpeed = 4.0f;
	arm->CameraLagMaxDistance = 1.0f;
	arm->bEnableCameraRotationLag = true;
	arm->CameraRotationLagSpeed = 8;
	arm->CameraLagMaxTimeStep = 1;

	cam = CreateDefaultSubobject<UCameraComponent>(TEXT("cam"));
	cam->SetupAttachment(lol, USpringArmComponent::SocketName);

	//gun
	gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("gun"));

	Collsion_component = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision_component"));
	Collsion_component->SetupAttachment(RootComponent);

	//Hands
	hands = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("hands"));
	hands->SetupAttachment(GetCapsuleComponent());

	//From where the bullet will launch
	Bullet_go = CreateDefaultSubobject<USceneComponent>(TEXT("Bullet_go"));
	Bullet_go->SetupAttachment(shit);

	fpp = true;


}

// Called when the game starts or when spawned
void APRO_IT_IS::BeginPlay()
{
	gun->AttachToComponent(hands, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("GripPoint"));
	Collsion_component->OnComponentBeginOverlap.AddDynamic(this, &ACharacter_Movement::OnOverlapBegin);
	Super::BeginPlay();
}

// Called every frame
void APRO_IT_IS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APRO_IT_IS::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	
	//Go to Project Settings -> Input to configure movement
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAction("Switch", IE_Pressed, this, &ACharacter_Movement::tpp);
	InputComponent->BindAxis("Vertical", this, &ACharacter_Movement::Forward_Back);
	InputComponent->BindAxis("Horizontal", this, &ACharacter_Movement::Left_Right);
	InputComponent->BindAxis("Horizontal_View", this, &ACharacter_Movement::Horizontal_View);
	InputComponent->BindAxis("Vertical_View", this, &ACharacter_Movement::Vertical_View);
	InputComponent->BindAction("Fire", IE_Pressed, this, &ACharacter_Movement::fire);
}

void APRO_IT_IS::tpp() {
	if (fpp == false) {
		lol->TargetArmLength = 0;
		fpp = true;
	}
	else {
		lol->TargetArmLength = 300;
		fpp = false;
	}
}

void ACharacter_Movement::Forward_Back(float value) {
	AddMovementInput(cam->GetForwardVector(), value);
}

void  ACharacter_Movement::Left_Right(float value) {
	AddMovementInput(cam->GetRightVector(), value);
}

void  ACharacter_Movement::Horizontal_View(float value) {
	arm->AddLocalRotation(FRotator(0.0f, value, 0.0f));
	hands->AddLocalRotation(FRotator(0.0f, value, 0.0f));
}

void  ACharacter_Movement::Vertical_View(float value) {
	if (value) {
		float temp = arm->GetRelativeRotation().Pitch + value; // The X axis
		if (temp < 25 && temp > -65) { // Not making the head to up by 25 and not to down by -65
			arm->AddLocalRotation(FRotator(value, 0, 0)); // If conditions meet then add the value
			hands->AddLocalRotation(FRotator(value, 0, 0));
		}
	}
}

void ACharacter_Movement::fire(){

	start = Bullet_go->GetComponentLocation();
	axis_of_the_worlds = Bullet_go->GetComponentRotation();

	//The FActorSpawnParamter passed to the spawn actor function.
	spawn.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	if(GetWorld()) {
		GetWorld()->SpawnActor<ABullet_man>(bullet_class_mesh , start , axis_of_the_worlds , spawn);
	}

	UGameplayStatics::PlaySoundAtLocation(this, Sound_Play , pen->GetComponentLocation());
}
