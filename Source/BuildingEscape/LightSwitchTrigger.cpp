

#include "LightSwitchTrigger.h"


// Sets default values
ALightSwitchTrigger::ALightSwitchTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CreatePointLight();
	CreateLightSphere();
}

void ALightSwitchTrigger::CreatePointLight()
{
	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Point light"));
	if (PointLight != nullptr)
	{
		PointLight->SetIntensity(LightIntensity);
		PointLight->SetVisibility(false);
		RootComponent = PointLight;
	}
}

void ALightSwitchTrigger::CreateLightSphere()
{
	if (PointLight != nullptr)
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
}




// Called when the game starts or when spawned
void ALightSwitchTrigger::BeginPlay()
{
	Super::BeginPlay();
	ToggleLight();

	LightSphere->SetSphereRadius(SphereRadius);
	DrawDebugSphere(GetWorld(), GetActorLocation(), SphereRadius, 50, FColor::Green, -1, 0, 2);
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
