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
	Death 
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
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float mMoveSpeed;

	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EPlayerAnimType mAnimType;

	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool	mOnGround;

public:
	void ChangeAnim(EPlayerAnimType AnimType)
	{
		mAnimType = AnimType;
	}




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

		
};
