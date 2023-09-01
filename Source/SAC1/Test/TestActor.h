// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h" //���������� gameinfo.h ��Ŭ���
#include "GameFramework/Actor.h"
#include "TestActor.generated.h"

UCLASS()
class SAC1_API ATestActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATestActor();


protected:
	/*
	���⿡ ������Ʈ ������ �����ߴٰ� ���� ����� ������Ʈ ������ ����
	�ƴϴ�. ���⿡ �̷��� �� ���� �ܼ��� ������ ������ �����ص� ���̴�.
	�׷��� ������ ���� ����� ������Ʈ�� �����ϰ� �� ������ ������ ������
	��ü�� �ּҸ� �Ѱ��־�� �Ѵ�.
	*/

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> mMesh;

	//������ �̿��� �浹 ������Ʈ�� �پ��� ������Ʈ�� �����ȴ�.
	//��ǥ������ ���� Ȱ��Ǵ� ������Ʈ�� �ڽ�, ��, ĸ���̴�.
	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> mBody;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	/*
	1������: �ε��� �浹ü�� ���´�.
	2������: �ε��� ���� ���Ͱ� ���´�.
	3������: �ε��� ���� ������ �浹ü�� � �浹ü������ ���´�.
	4������: ���� �ٵ� �ε����� ���´�.
	5������: �浹 �� ����� �����Ѵ�. (�̰� �� �����϶��Ͻ�)
	6������: �浹 ����� ���´�. �浹 ��ġ, �浹 ���, �浹���� �� �پ��� ������ 
	���´�!!! 6�� ���ڰ� �߿��ϴٰ� �ϼ���!!!

	UPROPERTY()
	int32 FaceIndex;

	UPROPERTY()
	float Time;

	UPROPERTY()  �浹 �Ÿ�
	float Distance;

	UPROPERTY()
	FVector_NetQuantize Location;

	UPROPERTY()  �ε��� ��ġ
	FVector_NetQuantize ImpactPoint;

	UPROPERTY()
	FVector_NetQuantizeNormal Normal;

	UPROPERTY()  �ε��� ����
	FVector_NetQuantizeNormal ImpactNormal;

	UPROPERTY()
	FVector_NetQuantize TraceStart;

	UPROPERTY()
	FVector_NetQuantize TraceEnd;

	UPROPERTY()
	float PenetrationDepth;

	UPROPERTY()
	int32 MyItem;

	UPROPERTY()
	int32 Item;

	UPROPERTY()
	uint8 ElementIndex;

	UPROPERTY()
	uint8 bBlockingHit : 1;

	UPROPERTY()
	uint8 bStartPenetrating : 1;

	UPROPERTY()
	TWeakObjectPtr<UPhysicalMaterial> PhysMaterial;

	UPROPERTY()
	FActorInstanceHandle HitObjectHandle;

	UPROPERTY()
	TWeakObjectPtr<UPrimitiveComponent> Component;

	UPROPERTY()
	FName BoneName;

	UPROPERTY()
	FName MyBoneName;
	*/
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

};
