// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Pawn.h"
#include "AIPawn.generated.h"

UCLASS()
class SAC1_API AAIPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAIPawn();

protected:
	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> mBody;

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> mMesh;

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UFloatingPawnMovement> mMovement;
	
	//������ ��������Ʈ�� �˰� �ְ� ���ش�.
	//��������Ʈ�� �̿��ؼ� ������ ��ü�� �ƴҰ�� None�� ���ִ�.
	TObjectPtr<class AAISpawnPoint> mSpawnPoint;

public:
	float GetHalfHeight() const
	{
		return mBody->GetScaledCapsuleHalfHeight(); 
	}
	
	void SetSpawnPoint(class AAISpawnPoint* SpawnPoint);
	
protected:
	 //Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//������ ��ü�� ���ŵ� �� ȣ��ȴ�.
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetCollisionProfile(const FName& Name);

};
 