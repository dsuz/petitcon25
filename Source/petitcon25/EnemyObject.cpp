#include "EnemyObject.h"

void AEnemyObject::Die_Implementation(AActor* DamageCauser)
{
	Destroy();
}

void AEnemyObject::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,
                             bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	Die(nullptr);
}

AEnemyObject::AEnemyObject()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyObject::BeginPlay()
{
	Super::BeginPlay();
	Life = MaxLife;	
}

void AEnemyObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AEnemyObject::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	Life -= DamageAmount;
	if (Life <= 0)
	{
		Die(DamageCauser);
	}
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

