

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SpotLightComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Public/DrawDebugHelpers.h"
#include "LightSwitchTrigger.generated.h"

UCLASS()
class BUILDINGESCAPE_API ALightSwitchTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightSwitchTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ToggleLight();
	void CreatePointLight();
	void CreateLightSphere();
	void AttachStaticMesh();

	UPROPERTY(VisibleAnywhere, Category = "Light Switch")
	UStaticMeshComponent* LightVisual;

	UPROPERTY(VisibleAnywhere, Category = "Light Switch")
	USpotLightComponent* PointLight;

	UPROPERTY(VisibleAnywhere, Category = "Light Switch")
	USphereComponent* LightSphere;

	UPROPERTY(EditAnywhere, Category = "Light Switch")
	float LightIntensity = 3000.0f;

	UPROPERTY(EditAnywhere, Category = "Light Switch")
	float SphereRadius = 300.0f;

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep, const
		FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOverlapEnd(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
};
