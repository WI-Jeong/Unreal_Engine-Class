// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActor.h" 
#include "../Player/PlayerCharacter.h" 

// Sets default values
ATestActor::ATestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*
	CreateDefaultSubobject:������ �����Լ��̴�. �����ڿ��� ������Ʈ�� �����ϱ� 
	���� �Լ��̴�. �� �Լ��� ���ø����� ������� �ִ�. �ֳ��ϸ�
	�پ��� ������Ʈ�� �����ϱ� �����ε� ���� ���ø��� �ƴ϶�� ������Ʈ �������� 
	������ �Լ��� �� ����� �־�� �Ѵ�. ������Ʈ�� 100������� 100���� �Լ��� ������
	�ϱ� ������ ���ø��� �̿��Ͽ� ������ ������Ʈ�� Ÿ���� �����ϸ� �ش� Ÿ���� ������Ʈ
	�� �����ϰ� �� ��ü�� �ּҸ� ��ȯ���ִ� ����̴�.
	*/
	mBody = CreateDefaultSubobject<UBoxComponent>(TEXT("Body"));

	//������ ������ body�� ��Ʈ ������Ʈ�� �Ǿ���Ѵ�. ��Ʈ������Ʈ=�θ�
	SetRootComponent(mBody);

	//������ ũ�⸦ �����Ѵ�.
	mBody->SetBoxExtent(FVector(84.0, 80.5, 77)); //���� Ÿ���̶� f�Ⱦ�

	// Overlap�� �����ϰ� �����Ѵ�.(�޽��� �浹�ϸ� �ȵǰ� �ڽ��� �浹�ؾ���)
	mBody->SetGenerateOverlapEvents(true);

	//�������� ����
	mBody->SetCollisionProfileName(TEXT("TestOverlap"));



	/*
	������ � �浹ü�鳢�� �浹 ���θ� �Ǹ��� ���ش�.
	�浹 ������ ��Ȳ�� ������ �̿��ϴ� ���α׷��Ӱ� ���� ������ �ؾ��Ѵ�.
	�׷��� ���� ���忡�� ���� �츮�� ����� ���۽�Ű�� ���ؼ� ������
	�Լ��� �𸥴�. �׷��Ƿ� �浹�� �Ǿ �ش� ����� ������ �Լ��� ȣ���� �� ���� 
	������ ����� ���۽�ų ���� ����. �׷��� �����ϴ� ����� ��������Ʈ�̴�. ��������Ʈ��
	���ؼ� �浹 ���Ŀ� ������ �Լ��� �ּҸ� ������Ʈ�� �Ѱ��شٸ� ��������Ʈ�� �� �Լ���
	�ּҸ� ������ �ִٰ� �������� �浹�� �Ͼ�� ������ �ִ� �Լ��� ȣ���Ͽ�
	�浹 �� ������ ������ ���۽����� �� �ְ� �ȴ�.
	�̷� ����� call back�̶�� ��
	*/



	//OnComponentBeginOverlap: ��ġ�� ������ �� ȣ���� �Լ��� ����ϴ� ��������Ʈ
	mBody->OnComponentBeginOverlap.AddDynamic(this, &ATestActor::OverlapBegin);

	//�޽� ������Ʈ�� �����Ѵ�.
	//ȭ�鿡 ����ϴ� ������Ʈ���� ��� UPrimitiveComponent�� ��ӹ޾�
	//������� �ִ�.
	mMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	//������ ������ MeshComponent�� �θ� ������Ʈ�� �ڽ��� �����Ѵ�. 
	mMesh->SetupAttachment(mBody);

	//Mesh�� �浹�� ����.
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//
	mMesh->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;

	//����� StaticMesh Asset�� ���´�.
	//�Ź� �����Ǵ� ��ü���� �ּ��� �ε��� �ʿ� ���� �ѹ��� �ε�� �� �յ���
	//Static���� �ε��Ѵ�.

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/NaturePackage/Meshes/flora/rock6.rock6'"));

	//Mesh�� �����°��� �����ߴٸ�
	if (MeshAsset.Succeeded())
	{
		//StaticMeshComponent�� ����� �������� �����Ѵ�.
		mMesh->SetStaticMesh(MeshAsset.Object);
	}

}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATestActor::OverlapBegin(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
	bool bFromSweep, const FHitResult& SweepResult)
{
	/*
#pragma region ���ϴ��̸�
	���⿡ �ִ� �ڵ带 ������ ��� �� �� �ְ� �ȴ�.
#pragma endregion ���ϴ��̸�
	*/

#pragma endregion CollisionActor
	//�÷��̾��� �ڸ� ���ϴ� ���⺤�͸� ���Ѵ�.
	FVector Back = OtherActor->GetActorForwardVector() * -1.f;

	//������ġ���ϱ�
	//GetActorLocation: �� ������ ���� ��ġ
	//BAck: �� ������ �ڸ� ���ϴ� ����
	//������ġ+��*300cm
	FVector Loc = OtherActor->GetActorLocation() + Back * 300.f;

	//������ �� ��ġ�� �̵���Ų��.
	//	OtherActor->SetActorLocation(Loc);

	//TeleportTo: ������ ��ġ�� ȸ���� �̿��ؼ� �ش� ��ġ �̵���Ű�� 
	// �ش� ȸ���� �����Ų��.
	//1������: �̵���ų ��ġ
	//2������: �̵� ���� ȸ����
	//3������: �˸��� ���۽�Ű�� �׽�Ʈ�� ��� true
	//4������: �̵���Ų ��ġ�� ��ġ�� ��ü�� �ִ��� üũ�� �ϱ� ���� ����̴�.

	OtherActor->TeleportTo(Loc, OtherActor->GetActorRotation(), false, true);

	//Cast�Լ��� ����ȯ�ϴ� Ÿ���� �ƴ� ��� nullptr�� ��ȯ�Ѵ�.
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);

		if (Player != nullptr)
		{
			Player->ChangeAnimation(EPlayerAnimType::Teleport);

			//�̵� �ӵ��� 0���� ������ش�.
			Player->GetCharacterMovement()->MaxWalkSpeed = 0.f;

		}
#pragma endregion CollisionActor


	
#pragma endregion CurrentActor 
		/*
	//�÷��̾��� �ڸ� ���ϴ� ���⺤�͸� ���Ѵ�.
	FVector Back = GetActorForwardVector() * -1.f;

	//������ġ���ϱ�
	//GetActorLocation: �� ������ ���� ��ġ
	//BAck: �� ������ �ڸ� ���ϴ� ����
	//������ġ+��*300cm
	FVector Loc = GetActorLocation() + Back * 300.f;

	//������ �� ��ġ�� �̵���Ų��.
	//OtherActor->SetActorLocation(Loc);

	//TeleportTo: ������ ��ġ�� ȸ���� �̿��ؼ� �ش� ��ġ �̵���Ű�� 
	// �ش� ȸ���� �����Ų��.
	//1������: �̵���ų ��ġ
	//2������: �̵� ���� ȸ����
	//3������: �˸��� ���۽�Ű�� �׽�Ʈ�� ��� true
	//4������: �̵���Ų ��ġ�� ��ġ�� ��ü�� �ִ��� üũ�� �ϱ� ���� ����̴�.

	TeleportTo(Loc,GetActorRotation(), false, true);
	*/
#pragma endregion CurrentActor 


}

