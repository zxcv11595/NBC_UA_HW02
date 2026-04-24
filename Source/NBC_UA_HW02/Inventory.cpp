// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "Engine/Engine.h"

// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

void UInventory::AddItem(FName ItemID)
{
	Inventory.Add(ItemID);

	UE_LOG(LogTemp, Warning, TEXT("아이템 추가: %s"), *ItemID.ToString());

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			10.0f,
			FColor::Green,
			FString::Printf(TEXT("아이템 추가: %s"), *ItemID.ToString())
		);
	}
}

void UInventory::AddTitle(FName TitleID)
{
	OwnedTitles.Add(TitleID);

	UE_LOG(LogTemp, Warning, TEXT("칭호 획득: %s"), *TitleID.ToString());

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			10.0f,
			FColor::Green,
			FString::Printf(TEXT("칭호 획득: %s"), *TitleID.ToString())
		);
	}
}

bool UInventory::CanUseItem(FName ItemID) const
{
	if (!Inventory.Contains(ItemID))
	{
		UE_LOG(LogTemp, Warning, TEXT("아이템 가방에 없음: %s"), *ItemID.ToString());

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				10.0f,
				FColor::Red,
				FString::Printf(TEXT("아이템 가방에 없음: %s"), *ItemID.ToString())
			);
		}
		return false;
	}

	const FItemData* ItemData = ItemDataMap.Find(ItemID);

	if (ItemData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("아이템 데이터 없음: %s"), *ItemID.ToString());

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				10.0f,
				FColor::Red,
				FString::Printf(TEXT("아이템 데이터 없음: %s"), *ItemID.ToString())
			);
		}

		return false;
	}

	if (ItemData->RequiredTitle.IsNone())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s 사용 가능: 필요 칭호 없음"), *ItemID.ToString());

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				10.0f,
				FColor::Green,
				FString::Printf(TEXT("%s 사용 가능: 필요 칭호 없음"), *ItemID.ToString())
			);
		}

		return true;
	}

	const bool bHasTitle = OwnedTitles.Contains(ItemData->RequiredTitle);

	UE_LOG(LogTemp, Warning, TEXT("%s / 필요 칭호: %s / 보유: %s"),
		*ItemID.ToString(),
		*ItemData->RequiredTitle.ToString(),
		bHasTitle ? TEXT("O") : TEXT("X"));

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			10.0f,
			bHasTitle ? FColor::Green : FColor::Red,
			FString::Printf(
				TEXT("%s / 필요 칭호: %s / 보유: %s"),
				*ItemID.ToString(),
				*ItemData->RequiredTitle.ToString(),
				bHasTitle ? TEXT("O") : TEXT("X")
			)
		);
	}

	return bHasTitle;
}

void UInventory::UseItem(FName ItemID)
{
	if (!CanUseItem(ItemID))
	{
		UE_LOG(LogTemp, Warning, TEXT("사용 실패: %s"), *ItemID.ToString());

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				10.0f,
				FColor::Red,
				FString::Printf(TEXT("사용 실패: %s"), *ItemID.ToString())
			);
		}

		return;
	}

	Inventory.RemoveSingle(ItemID);

	UE_LOG(LogTemp, Warning, TEXT("아이템 사용 성공: %s"), *ItemID.ToString());

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			10.0f,
			FColor::Green,
			FString::Printf(TEXT("아이템 사용 성공: %s"), *ItemID.ToString())
		);
	}
}




