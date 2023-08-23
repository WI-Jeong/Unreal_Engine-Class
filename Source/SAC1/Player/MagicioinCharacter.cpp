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
}
