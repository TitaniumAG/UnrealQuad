// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "QuadTreeActor.generated.h"


UCLASS()
class PROJECTQUADTREE_API AQuadTreeActor : public AActor
{
	GENERATED_BODY()

public:

	// Sets default values for this actor's properties
	AQuadTreeActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable, Category = "QuadtreeData")
		void InitialiseMesh();

	UFUNCTION(BlueprintCallable, Category = "QuadtreeData")
		void ApplyRecursions();

	void Subdivide(int pointA, int  pointB, int pointC);

	int indexA, indexB, indexC;

	UFUNCTION(BlueprintCallable, Category = "QuadtreeData")
		void ClearSections();


	void GenerateMesh();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		float ObjectScale;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		int Recursions;

	void buildTriangleBuffer();

	





	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		UProceduralMeshComponent * mesh;
	

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		TArray<FVector>Vertices;

	TArray<FVector>VerticesNew;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		TArray<int>Triangles;



	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
	TArray<FVector> Normals;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
	TArray<FProcMeshTangent> Tangents;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
	TArray<FVector2D> UV0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
	TArray<FLinearColor>VertexColors;

	


	

	


};
	
	