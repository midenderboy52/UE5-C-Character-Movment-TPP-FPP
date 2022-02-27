// Fill out your copyright notice in the Description page of Project Settings.


#include "PRO_IT_IS.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "Bullet_man.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "MyGameModeBase.h"
#include "InputCoreTypes.h"



// Sets default values
APRO_IT_IS::APRO_IT_IS()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;


	//The first paramater is the fat and the second one is the height
	GetCapsuleComponent()->SetCapsuleSize(100, 150);

	lol = CreateDefaultSubobject<USpringArmComponent>(TEXT("lol"));
	lol->SetupAttachment(GetCapsuleComponent());
	lol->TargetArmLength = 0;

	lol->bEnableCameraLag = true;
	lol->CameraLagSpeed = 4.0f;
	lol->CameraLagMaxDistance = 1.0f;
	lol->bEnableCameraRotationLag = true;
	lol->CameraRotationLagSpeed = 8;
	lol->CameraLagMaxTimeStep = 1;

	cam = CreateDefaultSubobject<UCameraComponent>(TEXT("cam"));
	cam->SetupAttachment(lol, USpringArmComponent::SocketName);

	//gun
	shit = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("shit"));

	liz = CreateDefaultSubobject<UBoxComponent>(TEXT("liz"));
	liz->SetupAttachment(RootComponent);

	//Hands
	sesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	sesh->SetupAttachment(GetCapsuleComponent());

	pen = CreateDefaultSubobject<USceneComponent>(TEXT("pen"));
	pen->SetupAttachment(shit);

	fpp = true;


}

// Called when the game starts or when spawned
void APRO_IT_IS::BeginPlay()
{
	shit->AttachToComponent(sesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("GripPoint"));
	liz->OnComponentBeginOverlap.AddDynamic(this, &APRO_IT_IS::OnOverlapBegin);
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
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAction("Switch", IE_Pressed, this, &APRO_IT_IS::lpp);
	InputComponent->BindAxis("Vertical", this, &APRO_IT_IS::Forward_Back);
	InputComponent->BindAxis("Horizontal", this, &APRO_IT_IS::Left_Right);
	InputComponent->BindAxis("Horizontal_View", this, &APRO_IT_IS::Horizontal_View);
	InputComponent->BindAxis("Vertical_View", this, &APRO_IT_IS::Vertical_View);
	InputComponent->BindAction("Fire", IE_Pressed, this, &APRO_IT_IS::fire);
}

void APRO_IT_IS::lpp() {
	if (fpp == false) {
		lol->TargetArmLength = 0;
		fpp = true;
	}
	else {
		lol->TargetArmLength = 300;
		fpp = false;
	}
}

void APRO_IT_IS::Forward_Back(float value) {
	AddMovementInput(cam->GetForwardVector(), value);
}

void APRO_IT_IS::Left_Right(float value) {
	AddMovementInput(cam->GetRightVector(), value);
}

void APRO_IT_IS::Horizontal_View(float value) {
	lol->AddLocalRotation(FRotator(0.0f, value, 0.0f));
	sesh->AddLocalRotation(FRotator(0.0f, value, 0.0f));
}

void APRO_IT_IS::Vertical_View(float value) {
	if (value) {
		float temp = lol->GetRelativeRotation().Pitch + value; // The X axis
		if (temp < 25 && temp > -65) { // Not making the head to up by 25 and not to down by -65
			lol->AddLocalRotation(FRotator(value, 0, 0)); // If conditions meet then add the value
			sesh->AddLocalRotation(FRotator(value, 0, 0));
		}
	}
}

void APRO_IT_IS::fire(){

	start = pen->GetComponentLocation();
	axis_of_the_worlds = pen->GetComponentRotation();

	//The FActorSpawnParamter passed to the spawn actor function.
	spawn.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	if(GetWorld()) {
		GetWorld()->SpawnActor<ABullet_man>(bullf , start , axis_of_the_worlds , spawn);
	}

	UGameplayStatics::PlaySoundAtLocation(this, hell, pen->GetComponentLocation());
}


void APRO_IT_IS::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const  FHitResult& SweepResult) {
	FString name = OtherComp->GetName();

	if(name.Contains("me_get_damaged")){
		health = health - 20;
	}

	if(health < 0 || health  == 0){
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("You Lost!")));

		AMyGameModeBase* lood = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));


		if(lood){
			lood->Restart_Gameplay(false);
		}

		Destroy();
	}
}