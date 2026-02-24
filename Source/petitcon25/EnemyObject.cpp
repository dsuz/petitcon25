#include "EnemyObject.h"
#include "Engine/DamageEvents.h"
#include "SideScrollingCharacter.h"

AEnemyObject::AEnemyObject()
{
	PrimaryActorTick.bCanEverTick = true;
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereComp->SetSimulatePhysics(true);
	SphereComp->SetCollisionProfileName(TEXT("BlockAll"));
	SphereComp->SetNotifyRigidBodyCollision(true);
	SetRootComponent(SphereComp);
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetCollisionProfileName(TEXT("NoCollision"));	// メッシュではなくSphereで当たり判定する
	StaticMeshComp->SetupAttachment(SphereComp);
}

void AEnemyObject::Activate_Implementation()
{
	for (auto Actor : ActorsSpawnedOnActivate)
	{
		auto Tx = GetActorTransform();
		FActorSpawnParameters SpawnInfo;
		GetWorld()->SpawnActor<AActor>(Actor.Get(), Tx.GetLocation(), Tx.Rotator(), SpawnInfo);
	}
}

void AEnemyObject::Die_Implementation(AActor* DamageCauser)
{
	for (auto Actor : ActorsSpawnedOnDeath)
	{
		auto Tx = GetActorTransform();
		FActorSpawnParameters SpawnInfo;
		GetWorld()->SpawnActor<AActor>(Actor.Get(), Tx.GetLocation(), Tx.Rotator(), SpawnInfo);
	}
	Destroy();
}

void AEnemyObject::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,
                             bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	if (auto Player = Cast<ASideScrollingCharacter>(Other))
	{
		// Die(Player);
		FDamageEvent DamageEvent;
		Player->TakeDamage(Damage, DamageEvent, nullptr, this);
	}	// プレイヤーに当たったらダメージを与え、消える
	else
	{
		Activate();
		// Die(nullptr);
	}	// 地面に落ちたら効果を発動し、消える
	Die(nullptr);
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

