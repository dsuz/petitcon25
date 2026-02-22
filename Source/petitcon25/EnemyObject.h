#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyObject.generated.h"

UCLASS()
class PETITCON25_API AEnemyObject : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	float Life = 0;
	float MaxLife = 1;
	UFUNCTION(BlueprintNativeEvent)
	void Die(AActor* DamageCauser);

public:
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved,
		FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	AEnemyObject();
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator,
		AActor* DamageCauser) override;
};
