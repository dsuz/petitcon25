#pragma once

UENUM(BlueprintType)
enum EPlayerMovementState
{
	Standing,
	JumpUp,
	JumpDown,
	Crouching,
};

UENUM(BlueprintType)
enum EHumanoidEnemyType
{
	Hugger,
	Boss,
};