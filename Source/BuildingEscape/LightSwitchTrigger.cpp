

#include "LightSwitchTrigger.h"


// Sets default values
ALightSwitchTrigger::ALightSwitchTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttachStaticMesh();
	CreatePointLight();
	CreateLightSphere();
}

void ALightSwitchTrigger::CreatePointLight()
{
	PointLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Point light"));
	if (PointLight != nullptr)
	{
		PointLight->SetIntensity(LightIntensity);
		PointLight->SetVisibility(false);
		PointLight->SetLightColor(FLinearColor(0.0f, 97.0f, 62.0f));
		PointLight->SetInnerConeAngle(20.0f);
		PointLight->SetOuterConeAngle(50.0f);
		PointLight->SetLightColor(FLinearColor(0.0f, 97.0f, 62.0f));
		PointLight->SetupAttachment(RootComponent);
	}
}

void ALightSwitchTrigger::CreateLightSphere()
{
	LightSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Light Sphere Comp"));
	if (LightSphere != nullptr)
	{
		LightSphere->InitSphereRadius(SphereRadius);
		LightSphere->SetCollisionProfileName(TEXT("Trigger"));
		LightSphere->SetupAttachment(RootComponent);

		LightSphere->OnComponentBeginOverlap.AddDynamic(this, &ALightSwitchTrigger::OnOverlapBegin);
		LightSphere->OnComponentEndOverlap.AddDynamic(this, &ALightSwitchTrigger::OnOverlapEnd);
	}
}

void ALightSwitchTrigger::AttachStaticMesh()
{
	LightVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Light Visual"));
	if (LightVisual != nullptr)
	{
		RootComponent = LightVisual;
		static ConstructorHelpers::FObjectFinder<UStaticMesh> LightVisualAsset(TEXT("/Game/torch"));
		if (LightVisualAsset.Succeeded())
		{
			LightVisual->SetStaticMesh(LightVisualAsset.Object);
			LightVisual->SetRelativeRotation(FRotator(90.0f, 90.0f, 0.0f));
			LightVisual->SetWorldScale3D(FVector(0.15f));
		}
	}
}


// Called when the game starts or when spawned
void ALightSwitchTrigger::BeginPlay()
{
	Super::BeginPlay();

	LightSphere->SetSphereRadius(SphereRadius);
}

// Called every frame
void ALightSwitchTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALightSwitchTrigger::ToggleLight()
{
	if (PointLight != nullptr)
	{
		PointLight->ToggleVisibility();
	}
}

void ALightSwitchTrigger::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep, const
	FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlapped!"))
		ToggleLight();
	}
}

void ALightSwitchTrigger::OnOverlapEnd(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		ToggleLight();
	}
}
