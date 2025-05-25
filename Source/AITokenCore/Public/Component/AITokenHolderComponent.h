// Copyright Lim Young.

#pragma once

#include "CoreMinimal.h"
#include "Core/AITokenHolder.h"
#include "Components/ActorComponent.h"
#include "AITokenHolderComponent.generated.h"


UCLASS(ClassGroup=(AITokenSystem), meta=(BlueprintSpawnableComponent))
class AITOKENCORE_API UAITokenHolderComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAITokenHolderComponent();
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FAITokenHolderConfig AITokenHolderConfig;

private:
	UPROPERTY(Transient)
	TObjectPtr<UAITokenHolder> AITokenHolder;

	void InitAITokenHolder();

public:
	UAITokenHolder* GetAITokenHolder() const;

	UFUNCTION(BlueprintCallable, Category = "AITokenHolder")
	FGameplayTag GetHeldTokenTag() const;

	UFUNCTION(BlueprintCallable, Category = "AITokenHolder")
	bool IsHoldingToken() const;
};
