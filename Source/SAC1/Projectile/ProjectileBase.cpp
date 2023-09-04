// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mBody = CreateDefaultSubobject< UBoxComponent>(TEXT("Body"));
	mMesh = CreateDefaultSubobject< UStaticMeshComponent>(TEXT("Mesh"));
	mMovement = CreateDefaultSubobject< UProjectileMovementComponent>(TEXT("Movement"));

	SetRootComponent(mBody);

	mMesh->SetupAttachment(mBody);

	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	mBody->SetCollisionProfileName(TEXT("BlockAll"));

	//ProjectileMovementComponent�� �̵����� ������Ʈ �� �������͸� �����Ѵ�.
	mMovement->SetUpdatedComponent(mBody);

	mMovement->InitialSpeed = 1000.f;

	mMovement->OnProjectileStop.AddDynamic(this, &AProjectileBase::ProjectileStop);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/BlueprintTest/Sphere1.Sphere1'"));

	if (MeshAsset.Succeeded())
	{
		mMesh->SetStaticMesh(MeshAsset.Object);
	}
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileBase::ProjectileStop(const FHitResult& ImpactResult)
{
	LOG(TEXT("Projectile Stop"));
	Destroy();
}

void AProjectileBase::SetMeshAsset(const FString& Path)
{
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, *Path);

	if (IsValid(Mesh))
	{
		mMesh->SetStaticMesh(Mesh);
	}
}

void AProjectileBase::SetCollisionProfile(const FName& Name)
{
	mBody->SetCollisionProfileName(Name);
}

