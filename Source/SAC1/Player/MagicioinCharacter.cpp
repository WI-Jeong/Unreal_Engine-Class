// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicioinCharacter.h"

AMagicioinCharacter::AMagicioinCharacter()
{
	//FObjectFinder : 애셋을 로딩해서 사용할 때 쓴다.
	//어떤 애셋을 불러올지 알 수 없기 때문에 template으로 구현되어 
	// 있고 template에 로딩하고자 하는 애셋의 타입을 지정해주면 된다.
	ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGideon/Characters/Heroes/Gideon/Skins/Tough/Meshes/Gideon_Tough.Gideon_Tough'"));

	if (MeshAsset.Succeeded())
	{
		//위에서 불러온 skeletalmesh를 character클래스가 가지고있는 
		//skeletalmeshcomponent에 지정해준다.
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}
}
