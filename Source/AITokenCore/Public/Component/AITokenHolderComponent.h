// Copyright Lim Young.

#pragma once

#include "CoreMinimal.h"
#include "Core/AITokenHolder.h"
#include "Components/ActorComponent.h"
#include "AITokenHolderComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AITOKENCORE_API UAITokenHolderComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAITokenHolderComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AITokenHolder")
	uint8 Priority = 0;

private:
	UPROPERTY()
	TObjectPtr<UAITokenHolder> AITokenHolder;

	void InitAITokenHolder();

public:
	UAITokenHolder* GetAITokenHolder() const;

	UFUNCTION(BlueprintCallable, Category = "AITokenHolder")
	FGameplayTag GetHeldTokenTag() const;
};
