// Fill out your copyright notice in the Description page of Project Settings.

#include "QuadTreeActor.h"
#include "Engine.h"
#include "EngineUtils.h"
#include "ModelDetailMedium.h"
#include "ModelDetailHigh.h"



// Sets default values
AQuadTreeActor::AQuadTreeActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// creating the procedural mesh component
	RootComponent = CreateAbstractDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("mesh"));

	
	

	mesh->AttachTo(RootComponent);
	
	ObjectScale = 1;

	indexA = 0;
	indexB = 1;
	indexC = 2;

	


}

void AQuadTreeActor::InitialiseMesh()
{
	//Super::PostActorCreated();

	GenerateMesh();
}

// Called when the game starts or when spawned
void AQuadTreeActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AQuadTreeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}








void AQuadTreeActor::GenerateMesh()
{
	
	//Vertices = { FVector(-100.000000, -100.000000, 0.000000),
	//FVector(100.000000, -100.000000, 0.000000),
	//FVector(-100.000000, 100.000000, 0.000000),
	//FVector(100.000000, 100.000000, 0.000000) };
	
	//2 3 1 
   // 2 4 3

	//Triangles = { 0,2,1,2,3,1 };

	// take object scale variable into account...
	for (int i = 0; i < Vertices.Num(); i++)
	{
		Vertices[i] = Vertices[i] * ObjectScale;
	}
	
	
	//mesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UV0, VertexColors, Tangents, true);
	

}


void AQuadTreeActor::ClearSections()
{
	mesh->ClearAllMeshSections();
}





void AQuadTreeActor::ApplyRecursions()
{



	for (int i = 0; i < Recursions; i++)
	{
		for(int j=0; j < Triangles.Num()/3; j++)
		{
			Subdivide(Triangles[indexA], Triangles[indexB], Triangles[indexC]);
			
		}

		Vertices = VerticesNew;
		Triangles.Empty();
		buildTriangleBuffer();
		VerticesNew.Empty();

		if (i == Recursions - 1)
		{
			
			
			mesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UV0, VertexColors, Tangents, true);
						
			
		}

		indexA = 0;
		indexB = 1;
		indexC = 2;

		
	}
}

void AQuadTreeActor::Subdivide(int pointA, int  pointB, int pointC)
{
	FVector a, b, c, ab, bc, ca;

	
		a = Vertices[pointA];
		b = Vertices[pointB];
		c = Vertices[pointC];

		ab = FMath::Lerp(a, b, 0.5);
		bc = FMath::Lerp(b, c, 0.5);
		ca = FMath::Lerp(c, a, 0.5);

		VerticesNew.Add(a);
		VerticesNew.Add(ab);
		VerticesNew.Add(ca);

		VerticesNew.Add(ca);
		VerticesNew.Add(bc);
		VerticesNew.Add(c);

		VerticesNew.Add(ab);
		VerticesNew.Add(b);
		VerticesNew.Add(bc);

		VerticesNew.Add(ab);
		VerticesNew.Add(bc);
		VerticesNew.Add(ca);


		indexA = indexA + 3;
		indexB = indexB + 3;
		indexC = indexC + 3;


		
}

void AQuadTreeActor::buildTriangleBuffer()
{
	for (int i = 0; i < Vertices.Num(); i++)
	{
		Triangles.Add(i);
	}
}





