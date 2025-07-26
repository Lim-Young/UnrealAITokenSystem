// Copyright Lim Young.

#pragma once

#include "CoreMinimal.h"
#include "Core/AITokenSource.h"
#include "Components/ActorComponent.h"
#include "AITokenSourceComponent.generated.h"


UCLASS(ClassGroup=(AITokenSystem), meta=(BlueprintSpawnableComponent))
class AITOKENCORE_API UAITokenSourceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAITokenSourceComponent();
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(Transient)
	TObjectPtr<UAITokenSource> AITokenSource;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AITokenSource")
	FAITokenSourceDefinition AITokenSourceDefinition;

protected:
	void InitAITokenSource();

public:
	UAITokenSource* GetAITokenSource() const;
};
