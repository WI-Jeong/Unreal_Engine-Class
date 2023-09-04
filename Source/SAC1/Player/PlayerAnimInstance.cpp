// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "PlayerCharacter.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	mAnimType = EPlayerAnimType::Default;

	mOnGround = false;

	mFallRecoveryAdditive = 0.f; 

	mAttackEnable = true;

	mAttackIndex = 0;

	mFallLandPositon = 0.14f;

	mCanJump = true;

}
void UPlayerAnimInstance::AttackT()
{
	//���� ���� ���°� true�̰� ���� ���� ��Ÿ�ְ� ��������ؾ��Ѵ�.
	if (!mAttackEnable || Montage_IsPlaying(mAttackMontage[mAttackIndex]))
		return;

	//���ݺҰ��ɻ��·� ������ش�.
	mAttackEnable = false;

	//���ݸ���� ó������ �����ų �� �յ����Ѵ�.
	Montage_SetPosition(mAttackMontage[mAttackIndex], 0.f);

	//��Ÿ�ָ� �����Ų��.
	Montage_Play(mAttackMontage[mAttackIndex]);

	//�迭.num() �迭�� ��
	mAttackIndex = (mAttackIndex + 1) % mAttackMontage.Num();

	 
}

void UPlayerAnimInstance::Jump()
{
	if (Montage_IsPlaying(mFallRecovery))
	{
		mFallRecoveryAdditive = 0.f;
		Montage_Stop(0.1f, mFallRecovery);
	}

	mCanJump = false;

	/*if (mAnimType == EPlayerAnimType::Fall)
	{
	   mFallRecoveryAdditive = 0.f;

	   if (Montage_IsPlaying(mFallRecovery))
		  Montage_Stop(0.1f, mFallRecovery);
	}*/
	
	mAnimType = EPlayerAnimType::Jump;

}

bool UPlayerAnimInstance::CanJump()
{
	return mCanJump;
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

			//mFallRecoveryAdditive = 0.f;

			/*
			* 1. ���� ��� �ִ� ���°� �ƴϴ�.
			* 2. ���� �����ϴ� �ִϸ��̼��� ������ �ƴϴ�.
			* 3. ���� �����ϴ� �ִϸ��̼��� Fall�� �ƴϴ�.
			* 
			*/

			if (!mOnGround && mAnimType != EPlayerAnimType::Fall &&
				mAnimType != EPlayerAnimType::Jump)
			{
				mAnimType = EPlayerAnimType::Fall;
			}

			//Default ���°� �ƴ� ��� ���� �Ұ��� ���·� ������ش�.
			if (mAnimType != EPlayerAnimType::Default)
			{
				mAttackEnable = false;
			}

			//���� ��� �ִ� �����̰� ���ϸ��̼��� fall�� ��� ���� �� ���� ��� �Ǿ��ٴ� ���̹Ƿ�
			//������ Ȱ��ȭ�Ѵ�.
			if (mOnGround && mAnimType == EPlayerAnimType::Fall)
			{
				mAttackEnable = true;
			}
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

	mFallRecoveryAdditive = 1.f;

	//���� ��Ÿ�ְ� ����ǰ� �ִ��� �Ǵ��Ѵ�.
	if (!Montage_IsPlaying(mFallRecovery))
	{
		//��Ŀ���� ����� ó������ �����ų �� �ֵ��� �Ѵ�.
		Montage_SetPosition(mFallRecovery, 0.f);

		//��Ÿ�ָ� �����Ų��.
		Montage_Play(mFallRecovery);

	}

	mCanJump = true;

	LOG(TEXT("FALL LAND"));

}

void UPlayerAnimInstance::AnimNotify_JumpRecoveryEnd()
{
	mFallRecoveryAdditive = 0.f;
}


void UPlayerAnimInstance::AnimNotify_Attack() 
{
	APlayerCharacter* Player = Cast< APlayerCharacter>(TryGetPawnOwner());

	// IsValid : ��ü�� ��ȿ���� �Ǵ��Ѵ�.
   // nullptr�� ��� ��ȿ�� ��ü�� �ƴϴ�.
	if (IsValid(Player))
	{
		Player->Attack1();
	}
}


void UPlayerAnimInstance::AnimNotify_Attack2()
{
	APlayerCharacter* Player = Cast< APlayerCharacter>(TryGetPawnOwner());

	// IsValid : ��ü�� ��ȿ���� �Ǵ��Ѵ�.
   // nullptr�� ��� ��ȿ�� ��ü�� �ƴϴ�.
	if (IsValid(Player))
	{
		Player->Attack2();
	}
}

//
void UPlayerAnimInstance::AnimNotify_Attack3()
{
	APlayerCharacter* Player = Cast< APlayerCharacter>(TryGetPawnOwner());

	// IsValid : ��ü�� ��ȿ���� �Ǵ��Ѵ�.
   // nullptr�� ��� ��ȿ�� ��ü�� �ƴϴ�.
	if (IsValid(Player))
	{
		Player->Attack3();
	}
}
//
void UPlayerAnimInstance::AnimNotify_AttackEnable()
{
	mAttackEnable = true;
}

void UPlayerAnimInstance::AnimNotify_AttackEnd()
{
	mAttackIndex = 0;
}

void UPlayerAnimInstance::AnimNotify_TeleportEnd()
{
	mAttackEnable = true;
	mAnimType = EPlayerAnimType::Default;

	APlayerCharacter* Player = Cast< APlayerCharacter>(TryGetPawnOwner());

	// IsValid : ��ü�� ��ȿ���� �Ǵ��Ѵ�.
   // nullptr�� ��� ��ȿ�� ��ü�� �ƴϴ�.
	if (IsValid(Player))
	{
		UCharacterMovementComponent* Movement = Player->GetCharacterMovement();

		if (IsValid(Movement))
		{
			Movement->MaxWalkSpeed = 600.f;
		}

	}
}
