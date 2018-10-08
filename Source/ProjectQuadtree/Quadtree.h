// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Quadtree.generated.h"

UCLASS()
class PROJECTQUADTREE_API AQuadtree : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuadtree();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		UProceduralMeshComponent * mesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		UProceduralMeshComponent * meshEdges;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
	TArray<FVector> Normals;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		TArray<FVector> NodeNormals;
	TArray<FVector> NodeNormalsNew;
	TArray<FVector> NodeNormalsCopy;

	

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
	TArray<FProcMeshTangent> Tangents;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
	TArray<FVector2D> UV0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
	TArray<FLinearColor>VertexColors;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		TArray<FLinearColor>NodeVertexColors;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		int MaxVertexCount;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		float ObjectScale;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		int NodeVertexCount;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		bool IsParentNode;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		bool IsChildNode;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		FVector NodePosition;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		TArray<FVector> Vertices;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		TArray<int> Triangles;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		TArray<FVector> NodeVertices;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		TArray<int>NodeTriangles;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		float MaxBoundsX;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		float MinBoundsX;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		float MaxBoundsY;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		float MinBoundsY;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		float MaxBoundsZ;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		float MinBoundsZ;




	////////////////////////////////////////////////////////////////////////////

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		float ParentMaxBoundsX;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		float ParentMinBoundsX;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		float ParentMaxBoundsY;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		float ParentMinBoundsY;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		float ParentMaxBoundsZ;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		float ParentMinBoundsZ;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		float ParentNodeBoundsScaleX;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		float ParentNodeBoundsScaleY;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		float ParentNodeBoundsScaleZ;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		bool InParentBounds;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		bool InChildBounds;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		FVector ParentNodePosition;

	UFUNCTION(BlueprintCallable, Category = "QuadtreeData")
	void InitialiseParentBounds();
	
	UFUNCTION(BlueprintCallable, Category = "QuadtreeData")
	void SetParentBounds(float inParentNodeBounsScaleX, float  inParentNodeBounsScaleY, float  inParentNodeBounsScaleZ, float inMaxBoundsX, float inMinBoundsX, float inMaxBoundsY, float inMinBoundsY, float inMaxBoundsZ, float inMinBoundsZ);

	UFUNCTION(BlueprintCallable, Category = "QuadtreeData")
	void HalfParentNodeBoundsScale(float inParentNodeBounsScaleX, float  inParentNodeBounsScaleY, float  inParentNodeBounsScaleZ);


	UFUNCTION(BlueprintCallable, Category = "QuadtreeData")
		void GetParentBounds(float &outParentNodeBounsScaleX, float &outParentNodeBounsScaleY, float &outParentNodeBounsScaleZ, float &outMaxBoundsX, float &outMinBoundsX, float &outMaxBoundsY, float &outMinBoundsY, float &outMaxBoundsZ, float &outMinBoundsZ);

	///////////////////////////////////////////////////////////////////////////








	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		float NodeBoundsScaleX;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		float NodeBoundsScaleY;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		float NodeBoundsScaleZ;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		FVector PositionOther;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		bool GeometryInSection;

	
	int indexA, indexB, indexC, indexA1, indexB1, indexC1, indexA2, indexB2, indexC2, indexA3, indexB3, indexC3;
	
	
	
	UFUNCTION(BlueprintCallable, Category = "QuadtreeData")
		void GetContainedVertices(int PointA, int PointB, int PointC);

	UFUNCTION(BlueprintCallable, Category = "QuadtreeData")
		void CountContainedVertices(int PointA1);
	// This function counts the number of vertices within its bounds. If the vertex count is greater than max vertices we want to subdivide this node, if not, we will build the mesh
	UFUNCTION(BlueprintCallable, Category = "QuadtreeData")
		bool InitialScanForVertices();
	
	UFUNCTION(BlueprintCallable, Category = "QuadtreeData")
		bool InitialScanForVerticesChildNode();

	UFUNCTION(BlueprintCallable, Category = "QuadtreeData")
		bool IsDesiredNodeSize(float MinNodeSize);
	
	UFUNCTION(BlueprintCallable, Category = "QuadtreeData")
		void CountContainedVerticesChildNode(int PointA1, int PointB1, int PointC1);

	UFUNCTION(BlueprintCallable, Category = "QuadtreeData")
		void ScanForVertices();

	UFUNCTION(BlueprintCallable, Category = "QuadtreeData")
		void InitialiseBounds();
	
	
	UFUNCTION(BlueprintCallable, Category = "QuadtreeData")
		void BuildTriangleBuffer();
	
	UFUNCTION(BlueprintCallable, Category = "QuadtreeData")
		void GenerateMesh();
	
	TArray<FVector> NodeVerticesCopy;

	TArray<int> NodeTrianglesCopy;

	TArray<FVector> NodeVerticesNew;

	UFUNCTION(BlueprintCallable, Category = "QuadtreeData")
		void ApplyRecursions();

	
	void Subdivide(int PointA2, int PointB2, int PointC2);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		int Recursions;


	UFUNCTION(BlueprintCallable, Category = "QuadtreeData")
		void ResetRecursions();

	UFUNCTION(BlueprintCallable, Category = "QuadtreeData")
		void HandleRecursionLevels();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		bool RecursiveLevel4;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		bool RecursiveLevel3;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		bool RecursiveLevel2;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		bool RecursiveLevel1;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		bool RecursionsReset;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
		FVector PlayerPos;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
	TArray<FVector> EdgeVertices;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "QuadtreeData")
	TArray<int> EdgeTriangles;


	UFUNCTION(BlueprintCallable, Category = "QuadtreeData")
		void GenerateEdgeVertices();

	UFUNCTION(BlueprintCallable, Category = "QuadtreeData")
		void GetEdgeVertices(int PointA, int PointB, int PointC);

	void BuildEdgeTriangleBuffer();

	UFUNCTION(BlueprintCallable, Category = "QuadtreeData")
		void BuildNormals();

	UFUNCTION(BlueprintCallable, Category = "QuadtreeData")
		void ResetAllIndexes();


	void CalculateNormals(int pointA, int pointB, int pointC);

	int indexA4, indexB4, indexC4, indexA5, indexB5, indexC5;



	void CalculateNormalsOther();
	
	


};
