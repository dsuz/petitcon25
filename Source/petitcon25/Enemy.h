// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class PETITCON25_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxLife = 1;
	float Life = 1;
	void Die(AActor* DamageCauser);
	void ActivateRagdoll();
	// ライフ0でこの距離離れたらActorを破棄する
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DistanceForDestroy = 700;
	UPROPERTY()
	TObjectPtr<APawn> PlayerPawn;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION(BlueprintCallable)
	virtual float TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator,
		AActor* DamageCauser) override;
};
