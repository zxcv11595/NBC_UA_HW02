// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"

USTRUCT(BlueprintType)
struct FItemData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FName ItemID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FText ItemName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FName RequiredTitle;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NBC_UA_HW02_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> Inventory;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FName, FItemData> ItemDataMap;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSet<FName> OwnedTitles;

public:
    UFUNCTION(BlueprintCallable)
    void AddItem(FName ItemID);

    UFUNCTION(BlueprintCallable)
    void AddTitle(FName TitleID);

    UFUNCTION(BlueprintCallable)
    bool CanUseItem(FName ItemID) const;

    UFUNCTION(BlueprintCallable)
    void UseItem(FName ItemID);
};
