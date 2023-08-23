// Copyright Epic Games, Inc. All Rights Reserved.


#include "SAC1GameModeBase.h"
#include "Player/MagicioinCharacter.h"

ASAC1GameModeBase::ASAC1GameModeBase()
{
	// Ŭ���� ���۷��� �ּ��� �ҷ������� �� ��� ������ ��ο��� 
	//���� �������� _C�� �ݵ�� �ٿ���� �Ѵ�.
	static ConstructorHelpers::FClassFinder<ACharacter> BlueprintPawn(TEXT("/Script/Engine.Blueprint'/Game/BlueprintTest/TestPlayerCharacter.TestPlayerCharacter_C'"));

	if (BlueprintPawn.Succeeded())
	{
		// DefaultPawnClass = BlueprintPawn.Class;
	 }


	//AMagicioinCharacter::StaticClass() : AMagicioinCharacter Ŭ������ 
	//Ŭ���� ���۷����� ���´�.
	DefaultPawnClass = AMagicioinCharacter::StaticClass();

}
