// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "GameFramework/GameplayCameraComponent.h"
#include "GameFramework/Character.h"
#include "SideScrollingCharacter.generated.h"

// class UCameraComponent;
class UInputAction;
struct FInputActionValue;

/**
 *  A player-controllable character side scrolling game
 */
UCLASS(abstract)
class ASideScrollingCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Player camera */
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="Camera", meta = (AllowPrivateAccess = "true"))
	// UCameraComponent* Camera;

protected:

	/** Move Input Action */
	// UPROPERTY(EditAnywhere, Category="Input")
	// UInputAction* MoveAction;
	//
	// /** Jump Input Action */
	// UPROPERTY(EditAnywhere, Category="Input")
	// UInputAction* JumpAction;
	//
	// /** Drop from Platform Action */
	// UPROPERTY(EditAnywhere, Category="Input")
	// UInputAction* DropAction;
	//
	// /** Interact Input Action */
	// UPROPERTY(EditAnywhere, Category="Input")
	// UInputAction* InteractAction;

	/** Impulse to manually push physics objects while we're in midair */
	UPROPERTY(EditAnywhere, Category="Side Scrolling|Jump")
	float JumpPushImpulse = 600.0f;

	/** Max distance that interactive objects can be triggered */
	UPROPERTY(EditAnywhere, Category="Side Scrolling|Interaction")
	float InteractionRadius = 200.0f;

	/** Time to disable input after a wall jump to preserve momentum */
	UPROPERTY(EditAnywhere, Category="Side Scrolling|Wall Jump")
	float DelayBetweenWallJumps = 0.3f;

	/** Distance to trace ahead of the character for wall jumps */
	UPROPERTY(EditAnywhere, Category="Side Scrolling|Wall Jump")
	float WallJumpTraceDistance = 50.0f;

	/** Horizontal impulse to apply to the character during wall jumps */
	UPROPERTY(EditAnywhere, Category="Side Scrolling|Wall Jump")
	float WallJumpHorizontalImpulse = 500.0f;

	/** Multiplies the jump Z velocity for wall jumps. */
	UPROPERTY(EditAnywhere, Category="Side Scrolling|Wall Jump")
	float WallJumpVerticalMultiplier = 1.4f;

	/** Collision object type to use for soft collision traces (dropping down floors) */
	UPROPERTY(EditAnywhere, Category="Side Scrolling|Soft Platforms")
	TEnumAsByte<ECollisionChannel> SoftCollisionObjectType;

	/** Distance to trace down during soft collision checks */
	UPROPERTY(EditAnywhere, Category="Side Scrolling|Soft Platforms")
	float SoftCollisionTraceDistance = 1000.0f;

	/** Last recorded time when this character started falling */
	float LastFallTime = 0.0f;

	/** Max amount of time that can pass since we started falling when we allow a regular jump */
	UPROPERTY(EditAnywhere, Category="Side Scrolling|Coyote Time", meta = (ClampMin = 0, ClampMax = 5, Units = "s"))
	float MaxCoyoteTime = 0.16f;

	/** Wall jump lockout timer */
	FTimerHandle WallJumpTimer;

	/** Last captured horizontal movement input value */
	float ActionValueY = 0.0f;

	/** Last captured platform drop axis value */
	float DropValue = 0.0f;

	/** If true, this character has already wall jumped */
	// bool bHasWallJumped = false;

	/** If true, this character has already double jumped */
	// bool bHasDoubleJumped = false;

	/** If true, this character is moving along the side scrolling axis */
	bool bMovingHorizontally = false;
	bool bCrouch = false;
	UPROPERTY(BlueprintReadWrite)
	float CrouchCameraRelativePositionZ = 0.0f;
	UPROPERTY(BlueprintReadWrite)
	float DefaultCameraRelativePositionZ = 0.0f;
	void AdjustCameraRelativePositionZ(float CameraRelativePositionZ);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UGameplayCameraComponent> GameplayCamera;
	float Life = 0;
	float MaxLife = 100;

public:
	
	/** Constructor */
	ASideScrollingCharacter();

protected:

	/** Gameplay cleanup */
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	/** Initialize input action bindings */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Collision handling */
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	/** Landing handling */
	virtual void Landed(const FHitResult& Hit) override;

	/** Handle movement mode changes to keep track of coyote time jumps */
	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode = 0) override;

protected:

	/** Called for movement input */
	UFUNCTION(BlueprintCallable, Category="Input")
	void Move(const FVector2D& Value);

protected:
	/** Called for drop from platform input */
	void Drop(const FInputActionValue& Value);

	/** Called for drop from platform input release */
	void DropReleased(const FInputActionValue& Value);

public:

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Forward);

	/** Handles drop inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoDrop(float Value);

	/** Handles jump pressed inputs from either controls or UI interfaces */
	// UFUNCTION(BlueprintCallable, Category="Input")
	// virtual void DoJumpStart();

	/** Handles jump pressed inputs from either controls or UI interfaces */
	// UFUNCTION(BlueprintCallable, Category="Input")
	// virtual void DoJumpEnd();

	/** Handles interact inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoInteract();

	virtual void BeginPlay() override;

protected:
	/** Handles advanced jump logic */
	// void MultiJump();
	/** Checks for soft collision with platforms */
	void CheckForSoftCollision();
	/** Resets wall jump lockout. Called from timer after a wall jump */
	// void ResetWallJump();
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void JumpIfGrounded();
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void StopJumpingIfInTheAir();
	UFUNCTION(BlueprintCallable, Category="Input")
	void Attack(UAnimMontage* Montage, UPrimitiveComponent* AttackBounds, float PlayRate = 1, bool bDisableMovement = true, bool bDisableInput = true);
	UFUNCTION()
	void OnMontageNotifyBegin(FName NotifyName,  const FBranchingPointNotifyPayload& Payload);
	UPROPERTY()
	TObjectPtr<UPrimitiveComponent> CurrentAttackBounds;	// 攻撃範囲のコリジョン
	UPROPERTY()
	TObjectPtr<UAnimInstance> AnimInstance;
	virtual void Crouch(bool bClientSimulation = false) override;
	virtual void UnCrouch(bool bClientSimulation = false) override;
	bool bAttacking = false;
	bool bStandupOnEndAttack = false;
	UFUNCTION(BlueprintCallable)
	EPlayerMovementState CheckCharacterMovementState();
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> HitReaction;

public:
	UFUNCTION(BlueprintCallable)
	virtual float TakeDamage(float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator,
		AActor* DamageCauser) override;

	/** Sets the soft collision response. True passes, False blocks */
	void SetSoftCollision(bool bEnabled);
	/** Returns true if the character has just double jumped */
	// UFUNCTION(BlueprintPure, Category="Side Scrolling")
	// bool HasDoubleJumped() const;

	/** Returns true if the character has just wall jumped */
	// UFUNCTION(BlueprintPure, Category="Side Scrolling")
	// bool HasWallJumped() const;
};
