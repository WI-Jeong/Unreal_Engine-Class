// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	mSpringArm->SetRelativeLocation(FVector(0.0, 0.0, 160.0));
	mSpringArm->SetRelativeRotation(FRotator(-10.0, 90.0, 0.0));
	mSpringArm->TargetArmLength = 500.f;

	//�θ� ������Ʈ�� Mesh�� �����Ѵ�.
	mSpringArm->SetupAttachment(GetMesh());

	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mCamera->SetupAttachment(mSpringArm);

	mCameraRotationEnable = false;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	// ������ �̺�Ʈ ������ ���ش�.
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);

	// �ùķ��̼� ��Ʈ �̺�Ʈ ������ ���ش�.
	//�������� �ùķ��̼��� �Ͼ ���� ȿ���� �ִ�.
	//�Ϲ� �̵��̳� �Ϲ����� �浹������ �ǹ̰� ����.
	GetCapsuleComponent()->SetNotifyRigidBodyCollision(true);

	// OnComponentHit : Multicast + Dynamic ������ Delegate�̴�.
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this,
		&APlayerCharacter::BodyHit);

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this,
		&APlayerCharacter::OverlapBegin);

	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this,
		&APlayerCharacter::OverlapEnd);

	GetCapsuleComponent()->CanCharacterStepUpOn =
		ECanBeCharacterBase::ECB_No;

	//GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// SkeletalMesh�� GetAnimInstance �Լ��� �������ְ� �ִ�.
	// �� �Լ��� SkeletalMesh�� ������ AnimInstance Ŭ������ �̿��ؼ� ����
	// �� ��ü�� ������ �ִ�.
	// GetAnimInstance�Լ��� �ٷ� �� ��ü�� �������� �Լ��̴�.
	mPlayerAnim = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//1�� ���� : ����� �̸�
	//2�� ���� : �Լ��� ȣ���� ��ü
	//3�� ���� : �Լ��� �ּ�
	PlayerInputComponent->BindAxis(TEXT("MoveFront"), this, 
		&APlayerCharacter::MoveFront);

	PlayerInputComponent->BindAxis(TEXT("MoveSide"), this,
		&APlayerCharacter::MoveSide);

	PlayerInputComponent->BindAxis(TEXT("RotationCharacter"), this,
		&APlayerCharacter::RotationCharacterYaw);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this,
		&APlayerCharacter::UpDownPitch);


	PlayerInputComponent->BindAxis(TEXT("CameraZoom"), this,
		&APlayerCharacter::CameraZoom);



	PlayerInputComponent->BindAction(TEXT("RotationCamera"),
		EInputEvent::IE_Pressed,this,
		&APlayerCharacter::RotationCamera);

	PlayerInputComponent->BindAction(TEXT("RotationCamera"),
		EInputEvent::IE_Released, this,
		&APlayerCharacter::RotationCameraReleased); 

	PlayerInputComponent->BindAction(TEXT("Attack"),
		EInputEvent::IE_Pressed, this,
		&APlayerCharacter::Attack); 

	PlayerInputComponent->BindAction(TEXT("Jumpkey"),
		EInputEvent::IE_Pressed, this,
		&APlayerCharacter::Jumpkey);
}

void APlayerCharacter::MoveFront(float Scale)
{
	AddMovementInput(GetActorForwardVector(), Scale);

	// Scale�� 0�� �ƴ� ���� �̵�Ű�� �����ٴ� ���̹Ƿ� �ִϸ��̼���
	// Default�� �����Ѵ�.
	/*if (Scale != 0.f)
		mPlayerAnim->ChangeAnim(EPlayerAnimType::Default);*/
}

void APlayerCharacter::MoveSide(float Scale)
{
	AddMovementInput(GetActorRightVector(), Scale);
}


void APlayerCharacter::RotationCharacterYaw(float Scale)
{
	if (mCameraRotationEnable)
	{
		float Rot = 180.f * GetWorld()->GetDeltaSeconds() * Scale;

		mSpringArm->AddRelativeRotation(FRotator(0.0, (double)Rot, 0.0));
	
	}

	else
	{
		AddControllerYawInput(Scale);
	}
}

void APlayerCharacter::UpDownPitch (float Scale)
{
	if (mCameraRotationEnable)
	{
		float Rot = 180.f * GetWorld()->GetDeltaSeconds() * Scale;

		mSpringArm->AddRelativeRotation(FRotator((double)Rot,0.0, 0.0));

	}

	
}

void APlayerCharacter::CameraZoom(float Scale)
{
	float Length = Scale * 50.f;

	mSpringArm->TargetArmLength -= Length;


}

void APlayerCharacter::RotationCamera()
{
	mCameraRotationEnable = true;
}

void APlayerCharacter::RotationCameraReleased()
{
	mCameraRotationEnable = false;
}

void APlayerCharacter::Jumpkey()
{
	if (CanJump()&&mPlayerAnim->CanJump()) //���� ���� �������� üũ�Ѵ�.
	{
		Jump();
		mPlayerAnim->Jump();
		//mPlayerAnim->ChangeAnim(EPlayerAnimType::Jump);
	}
}

void APlayerCharacter::Attack()
{
	mPlayerAnim->AttackT();
}

void APlayerCharacter::BodyHit(UPrimitiveComponent* HitComponent, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, 
		FString::Printf(TEXT("Dest : %s"),*OtherActor->GetName()));
}

void APlayerCharacter::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red,
		FString::Printf(TEXT("BeginOverlap Dest : %s"), *OtherActor->GetName()));
}

void APlayerCharacter::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red,
		FString::Printf(TEXT("EndOverlap Dest : %s"), *OtherActor->GetName()));
}

void APlayerCharacter::Attack1()
{
}

void APlayerCharacter::Attack2()
{
}

/// 
void APlayerCharacter::Attack3()
{
}

///
 