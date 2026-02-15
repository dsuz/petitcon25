// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemy::AEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Life = MaxLife;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
}

void AEnemy::Die(AActor* DamageCauser)
{
	ActivateRagdoll();
	// ふっとばす
	auto Direction = -1 * GetActorForwardVector();
	if (DamageCauser)
	{
		auto PlayerLocation = DamageCauser->GetActorLocation();
		Direction = GetActorLocation() - PlayerLocation;
	}
	Direction += GetActorRightVector() * FMath::RandRange(-2, 2);
	Direction += GetActorUpVector() * FMath::RandRange(0, 3);
	GetMesh()->AddImpulse(Direction * 100, TEXT("pelvis"));
}

void AEnemy::ActivateRagdoll()
{
	if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
	{
		MoveComp->DisableMovement();
	}

	// Disable player input
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		DisableInput(PC);
	}

	// Detach controller (optional)
	DetachFromControllerPendingDestroy();

	// Set collision profile for ragdoll
	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));

	// Enable physics simulation on all bones
	GetMesh()->SetAllBodiesSimulatePhysics(true);
	GetMesh()->WakeAllRigidBodies();
	GetMesh()->bBlendPhysics = true;
	
	// 敵の残骸がプレイヤーを妨害しないようにする
	auto Capsule = GetCapsuleComponent();
	Capsule->SetCollisionProfileName(TEXT("Ragdoll"));
}

float AEnemy::TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator,
                         AActor* DamageCauser)
{
	if (Life > 0)
	{
		Life -= Damage;
		if (Life <= 0)
		{
			Life = 0;
			Die(DamageCauser);	// DamageCauser can be null;
		}
	}
	return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PlayerPawn && Life <= 0)
	{
		float DistanceToPlayer = FVector::Distance(GetActorLocation(), PlayerPawn->GetActorLocation());
		if (DistanceToPlayer > DistanceForDestroy)
		{
			Destroy();
		}
	}
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

