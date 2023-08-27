// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicioinCharacter.h"

AMagicioinCharacter::AMagicioinCharacter()
{
	//FObjectFinder : 애셋을 로딩해서 사용할 때 쓴다.
	//어떤 애셋을 불러올지 알 수 없기 때문에 template으로 구현되어 
	// 있고 template에 로딩하고자 하는 애셋의 타입을 지정해주면 된다.
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGideon/Characters/Heroes/Gideon/Skins/Tough/Meshes/Gideon_Tough.Gideon_Tough'"));

	if (MeshAsset.Succeeded())
	{
		//위에서 불러온 skeletalmesh를 character클래스가 가지고있는 
		//skeletalmeshcomponent에 지정해준다.
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}

	LOG(TEXT("Log Test"));


	//Animation Blueprint 클래스 레퍼런스를 얻어온다.
	static ConstructorHelpers::FClassFinder <UAnimInstance> AnimClass(TEXT("/Script/Engine.AnimBlueprint'/Game/Player/AB_Magicion.AB_Magicion_C'"));  
	
	if (AnimClass.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimClass.Class);

	//캡슐의 절반높이는 기본 88로 되어있지만 메쉬의 키가 커서 92로 설정한다.
	GetCapsuleComponent()->SetCapsuleHalfHeight(92.f);
	
	//캡슐의 절반높이가 92로 설정되었기 때문에 기본 메시 출력은 
	//캡슐의 가운데를 발로 밟고 옆을 바라보게 하여 출력되어 있으므로
	//캡슐의 절반높이인 92만큼 아래로 내려준다.
	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -92.0));

	//메시가 전방을 바라보게 회전한다.
	GetMesh()->SetRelativeRotation(FRotator(0.0,-90.0,0.0));

}
