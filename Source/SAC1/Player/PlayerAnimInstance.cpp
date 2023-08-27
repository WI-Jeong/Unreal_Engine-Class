// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "PlayerCharacter.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	mAnimType = EPlayerAnimType::Default;

	mOnGround = false;
}

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	//�θ�Ŭ������ NativeInitializeAnimation()�Լ��� ����ȣ�����ش�.
	//Super: �θ�Ŭ������ �ǹ��Ѵ�.

	Super::NativeInitializeAnimation();
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//Cast: �𸮾󿡼� �����ϴ� ������ ����ȯ �Լ��̴�.
	// �𸮾� Ŭ�������� �ݵ�� cast �Լ��� �̿��ؼ� ����ȯ�ؾ��Ѵ�.
	APlayerCharacter*Player=Cast< APlayerCharacter>(TryGetPawnOwner());

	// IsValid : ��ü�� ��ȿ���� �Ǵ��Ѵ�.
   // nullptr�� ��� ��ȿ�� ��ü�� �ƴϴ�.
	if (IsValid(Player)) 
	{
		UCharacterMovementComponent* Movement = Player->GetCharacterMovement(); 

		if (IsValid(Movement)) 
		{
			mMoveSpeed = Movement->Velocity.Length(); 

			mOnGround = Movement->IsMovingOnGround();
		}
	}

	//check�� C++�� assert����̴�.
	//check��ȣ ���� ������ false�� ��� ������ �߻���Ų��.
	//check(Player != nullptr); 

	//checkf�� ���� �߻��� �޼����� ����� �� �� �ִ�.
	//checkf(Player != nullptr, TEXT("Player Cast Failed"));

}

void UPlayerAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

void UPlayerAnimInstance::NativePostEvaluateAnimation()
{
	Super::NativePostEvaluateAnimation();
}

void UPlayerAnimInstance::NativeUninitializeAnimation()
{
	Super::NativeUninitializeAnimation();
}

void UPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UPlayerAnimInstance::AnimNotify_TransitionFall()
{
	mAnimType = EPlayerAnimType::Fall;
}

void UPlayerAnimInstance::AnimNotify_FallLandEnd()
{
	mAnimType = EPlayerAnimType::Default;
}
