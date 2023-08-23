// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicioinCharacter.h"

AMagicioinCharacter::AMagicioinCharacter()
{
	//FObjectFinder : �ּ��� �ε��ؼ� ����� �� ����.
	//� �ּ��� �ҷ����� �� �� ���� ������ template���� �����Ǿ� 
	// �ְ� template�� �ε��ϰ��� �ϴ� �ּ��� Ÿ���� �������ָ� �ȴ�.
	ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGideon/Characters/Heroes/Gideon/Skins/Tough/Meshes/Gideon_Tough.Gideon_Tough'"));

	if (MeshAsset.Succeeded())
	{
		//������ �ҷ��� skeletalmesh�� characterŬ������ �������ִ� 
		//skeletalmeshcomponent�� �������ش�.
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}

	
	//ĸ���� ���ݳ��̴� �⺻ 88�� �Ǿ������� �޽��� Ű�� Ŀ�� 90�� �����Ѵ�.
	GetCapsuleComponent()->SetCapsuleHalfHeight(92.f);
	
	//ĸ���� ���ݳ��̰� 92�� �����Ǿ��� ������ �⺻ �޽� ����� 
	//ĸ���� ����� �߷� ��� ���� �ٶ󺸰� �Ͽ� ��µǾ� �����Ƿ�
	//ĸ���� ���ݳ����� 92��ŭ �Ʒ��� �����ش�.
	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -92.0));


	//�޽ð� ������ �ٶ󺸰� ȸ���Ѵ�.
	GetMesh()->SetRelativeRotation(FRotator(0.0,-90.0,0.0));

}
