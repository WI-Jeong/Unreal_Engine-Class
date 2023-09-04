// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

//uint8=>1byte ��ȣ ���� �����̴�. 0~255���� ǥ�� �����ϴ�.
UENUM(BluePrintType)
enum class EPlayerAnimType : uint8
{
	Default,
	Jump,
	Fall,
	Death,
	Teleport
};

/**
 * 
 */
UCLASS()
class SAC1_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPlayerAnimInstance(); 
	
protected:
	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float mMoveSpeed;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EPlayerAnimType mAnimType;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool	mOnGround;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float mFallRecoveryAdditive; 

	UPROPERTY(Category = Data, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage>	mFallRecovery;

	UPROPERTY(Category = Data, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray< TObjectPtr<UAnimMontage>>	mAttackMontage;

	UPROPERTY(Category = Data, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float mFallLandPositon;


	bool mAttackEnable;
	int32 mAttackIndex;
	bool mCanJump;


public:
	void ChangeAnim(EPlayerAnimType AnimType)
	{
		mAnimType = AnimType;
	}

	void AttackT();
	void Jump();
	bool CanJump(); 

public:

	virtual void NativeInitializeAnimation();

	virtual void NativeUpdateAnimation(float DeltaSeconds);

	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds);

	virtual void NativePostEvaluateAnimation();

	virtual void NativeUninitializeAnimation();

	virtual void NativeBeginPlay();




public:

	//��Ƽ���� �Լ��� ����Ÿ���� void�� 
	//AnimNotify_��Ƽ�����̸�()�� ���·� �Լ��� �����ؾ��Ѵ�.
	UFUNCTION()
	
	void AnimNotify_TransitionFall(); 

	UFUNCTION()

	void AnimNotify_FallLandEnd();

	UFUNCTION()
	void AnimNotify_JumpRecoveryEnd();


	UFUNCTION()
	void AnimNotify_Attack();

	UFUNCTION()
	void AnimNotify_Attack2();

	//
	UFUNCTION()
	void AnimNotify_Attack3();
	//

	UFUNCTION()
	void AnimNotify_AttackEnable();


	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_TeleportEnd();

};
