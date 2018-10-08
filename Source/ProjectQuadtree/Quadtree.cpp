// Fill out your copyright notice in the Description page of Project Settings.

#include "Quadtree.h"


// Sets default values
AQuadtree::AQuadtree()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = CreateAbstractDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("mesh"));
	mesh->AttachTo(RootComponent);

	meshEdges = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("meshEdges"));
	meshEdges->AttachTo(RootComponent);

	
	
	

	GeometryInSection = false;

	indexA = 0;
	indexB = 1;
	indexC = 2;

	indexA1 = 0;
	indexB1 = 1;
	indexC1 = 2;

	indexA2 = 0;
	indexB2 = 1;
	indexC2 = 2;
	
	indexA3 = 0;
	indexB3 = 1;
	indexC3 = 2;

	indexA4 = 0;
	indexB4 = 1;
	indexC4 = 2;

	indexA5 = 0;
	indexB5 = 1;
	indexC5 = 2;


	

}

// Called when the game starts or when spawned
void AQuadtree::BeginPlay()
{
	Super::BeginPlay();

	
	
}

// Called every frame
void AQuadtree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void AQuadtree::GetContainedVertices(int PointA, int PointB, int PointC)
{


		if (FVector(Vertices[PointA] + Vertices[PointB] + Vertices[PointC]).X /3 + PositionOther.X > MinBoundsX &&
			FVector(Vertices[PointA] + Vertices[PointB] + Vertices[PointC]).X /3 + PositionOther.X < MaxBoundsX &&
			FVector(Vertices[PointA] + Vertices[PointB] + Vertices[PointC]).Y /3 + PositionOther.Y > MinBoundsY &&
			FVector(Vertices[PointA] + Vertices[PointB] + Vertices[PointC]).Y /3 + PositionOther.Y < MaxBoundsY &&
			FVector(Vertices[PointA] + Vertices[PointB] + Vertices[PointC]).Z /3 + PositionOther.Z > MinBoundsZ &&
			FVector(Vertices[PointA] + Vertices[PointB] + Vertices[PointC]).Z /3 + PositionOther.Z < MaxBoundsZ)
		{

			NodeVertices.Add(Vertices[PointA]);
			NodeVertices.Add(Vertices[PointB]);
			NodeVertices.Add(Vertices[PointC]);

			NodeNormals.Add(Normals[PointA]);
			NodeNormals.Add(Normals[PointB]);
			NodeNormals.Add(Normals[PointC]);
			
			NodeVertexColors.Add(VertexColors[PointA]);
			NodeVertexColors.Add(VertexColors[PointB]);
			NodeVertexColors.Add(VertexColors[PointC]);
			

			indexA = indexA + 3;
			indexB = indexB + 3;
			indexC = indexC + 3;


		}
		else
		{

			

			indexA = indexA + 3;
			indexB = indexB + 3;
			indexC = indexC + 3;

		}


}



		
			

	


bool AQuadtree::InitialScanForVertices()
{
	for (int i = 0; i < Vertices.Num(); i++)
	{
		CountContainedVertices(Triangles[indexA1]);
	}

	if (NodeVertexCount > MaxVertexCount)
	{
		return true;
		
	}
	else
	{
		return false;
	}
}



bool AQuadtree::InitialScanForVerticesChildNode()
{
	for (int i = 0; i < NodeVertices.Num(); i++)
	{
		//CountContainedVertices(NodeTriangles[indexA1], NodeTriangles[indexB1], NodeTriangles[indexC1]);
	}

	if (NodeVertexCount > 0 && NodeVertexCount >= MaxVertexCount)
	{
		return true;

	}
	else
	{
		return false;
	}
}




void AQuadtree::ScanForVertices()
{
	for (int i = 0; i < Triangles.Num()/3; i++)
	{
		GetContainedVertices(Triangles[indexA], Triangles[indexB], Triangles[indexC]);
	}
}


void AQuadtree::InitialiseBounds()
{
	// max bounds x 
	MaxBoundsX = NodePosition.X + NodeBoundsScaleX;


	MinBoundsX = NodePosition.X - NodeBoundsScaleX;
	

	// max bounds y
	MaxBoundsY = NodePosition.Y + NodeBoundsScaleY;
	

	MinBoundsY = NodePosition.Y - NodeBoundsScaleY;
	

	// max bounds z
	MaxBoundsZ = NodePosition.Z + NodeBoundsScaleZ;
	

	MinBoundsZ = NodePosition.Z - NodeBoundsScaleZ;
	
}

void AQuadtree::BuildTriangleBuffer()
{
	for (int i = 0; i < NodeVertices.Num(); i++)
	{
		NodeTriangles.Add(i);
		Normals.Add(FVector(0, 0, 1));;
		
	}

	

	
}

void AQuadtree::GenerateMesh()
{
	for (int i = 0; i < NodeVertices.Num(); i++)
	{
		NodeVertices[i] = NodeVertices[i] * ObjectScale;
		
	}
	NodeVerticesCopy = NodeVertices;
	NodeTrianglesCopy = NodeTriangles;
	NodeNormalsCopy = NodeNormals;
	mesh->CreateMeshSection_LinearColor(0, NodeVertices, NodeTriangles, NodeNormals, UV0, NodeVertexColors, Tangents, true);
	if (NodeVertices.Num() > 0)
	{
		GeometryInSection = true;
	}
	
	

}

void AQuadtree::ApplyRecursions()
{
	for (int i = 0; i < Recursions; i++)
	{
		for (int j = 0; j < NodeTriangles.Num() / 3; j++)
		{
			Subdivide(NodeTriangles[indexA2], NodeTriangles[indexB2], NodeTriangles[indexC2]);
		}

		NodeTriangles.Empty();

		NodeVertices = NodeVerticesNew;
		NodeNormals = NodeNormalsNew;
		NodeVerticesNew.Empty();
		NodeNormalsNew.Empty();
		NodeTriangles.Empty();
		BuildTriangleBuffer();
		indexA2 = 0;
		indexB2 = 1;
		indexC2 = 2;

		if (i == Recursions - 1)
		{
			mesh->CreateMeshSection_LinearColor(0, NodeVertices, NodeTriangles, NodeNormals, UV0, VertexColors, Tangents, true);
		}


	}
}

void AQuadtree::Subdivide(int PointA2, int PointB2, int PointC2)
{
	
		FVector A2, B2, C2, A2B2, B2C2, C2A2;

		FVector NA, NB, NC, NAB, NBC, NCA;

		A2 = NodeVertices[PointA2];
		NA = NodeNormals[PointA2];

		B2 = NodeVertices[PointB2];
		NB = NodeNormals[PointB2];

		C2 = NodeVertices[PointC2];
		NC = NodeNormals[PointC2];

		A2B2 = FMath::Lerp(A2, B2, 0.5);
		NAB = FMath::Lerp(NA, NB, 0.5);

		B2C2 = FMath::Lerp(B2, C2, 0.5);
		NBC = FMath::Lerp(NB, NC, 0.5);

		C2A2 = FMath::Lerp(C2, A2, 0.5);
		NCA = FMath::Lerp(NC, NA, 0.5);

		//#1
		NodeVerticesNew.Add(A2);
		NodeVerticesNew.Add(A2B2);
		NodeVerticesNew.Add(C2A2);
		NodeNormalsNew.Add(NA);
		NodeNormalsNew.Add(NAB);
		NodeNormalsNew.Add(NCA);



		//#2
		NodeVerticesNew.Add(A2B2);
		NodeVerticesNew.Add(B2);
		NodeVerticesNew.Add(B2C2);
		NodeNormalsNew.Add(NAB);
		NodeNormalsNew.Add(NB);
		NodeNormalsNew.Add(NBC);



		//#3
		NodeVerticesNew.Add(C2A2);
		NodeVerticesNew.Add(B2C2);
		NodeVerticesNew.Add(C2);
		NodeNormalsNew.Add(NCA);
		NodeNormalsNew.Add(NBC);
		NodeNormalsNew.Add(NC);



		//#4
		NodeVerticesNew.Add(C2A2);
		NodeVerticesNew.Add(A2B2);
		NodeVerticesNew.Add(B2C2);
		NodeNormalsNew.Add(NCA);
		NodeNormalsNew.Add(NAB);
		NodeNormalsNew.Add(NBC);



		indexA2 = indexA2 + 3;
		indexB2 = indexB2 + 3;
		indexC2 = indexC2 + 3;
	}


void AQuadtree::ResetRecursions()
{
	NodeVertices = NodeVerticesCopy;
	NodeTriangles = NodeTrianglesCopy;
	NodeNormals = NodeNormalsCopy;
	mesh->CreateMeshSection_LinearColor(0, NodeVertices, NodeTriangles, NodeNormals, UV0, VertexColors, Tangents, true);
}



void AQuadtree::HandleRecursionLevels()
{

	if (PlayerPos.X > MinBoundsX  &&
		PlayerPos.X < MaxBoundsX  &&
		PlayerPos.Y > MinBoundsY  &&
		PlayerPos.Y < MaxBoundsY  &&
		PlayerPos.Z > MinBoundsZ  &&
		PlayerPos.Z < MaxBoundsZ  &&
		GeometryInSection == true &&
		IsParentNode == true)
	{
		InParentBounds = true;
	}
	else
	{
		InParentBounds = false;
	}







	if (PlayerPos.X > MinBoundsX  &&
		PlayerPos.X < MaxBoundsX  &&
		PlayerPos.Y > MinBoundsY  &&
		PlayerPos.Y < MaxBoundsY  &&
		PlayerPos.Z > MinBoundsZ  &&
		PlayerPos.Z < MaxBoundsZ  &&
		GeometryInSection == true &&
		IsChildNode == true)
	{
		
		InChildBounds = true;		
	}
	else
	{
		if (GeometryInSection == true && 
			IsChildNode == true)
		{
			InChildBounds = false;
		}

	}

	
	
	
	
	

}


	



void AQuadtree::CountContainedVertices(int PointA1)
{
	//if (Vertices.IsValidIndex(PointA1))
	//{

		if (Vertices[PointA1].X > MinBoundsX &&
			Vertices[PointA1].X < MaxBoundsX &&
			Vertices[PointA1].Y > MinBoundsY &&
			Vertices[PointA1].Y < MaxBoundsY &&
			Vertices[PointA1].Z > MinBoundsZ &&
			Vertices[PointA1].Z < MaxBoundsZ)
		{
			NodeVertexCount++;
			indexA1 = indexA1 + 3;
		}


		else
		{
			
			indexA1 = indexA1 + 3;
		}


	//}
			
				
		
	}



void AQuadtree::CountContainedVerticesChildNode(int PointA1, int PointB1, int PointC1)
{
	if (Vertices.IsValidIndex(PointA1))
	{

		if (Vertices[PointA1].X + PositionOther.X > MinBoundsX &&
			Vertices[PointA1].X + PositionOther.X < MaxBoundsX &&
			Vertices[PointA1].Y + PositionOther.Y > MinBoundsY &&
			Vertices[PointA1].Y + PositionOther.Y < MaxBoundsY &&
			Vertices[PointA1].Z + PositionOther.Z > MinBoundsZ &&
			Vertices[PointA1].Z + PositionOther.Z < MaxBoundsZ &&

			Vertices[PointB1].X + PositionOther.X > MinBoundsX &&
			Vertices[PointB1].X + PositionOther.X < MaxBoundsX &&
			Vertices[PointB1].Y + PositionOther.Y > MinBoundsY &&
			Vertices[PointB1].Y + PositionOther.Y < MaxBoundsY &&
			Vertices[PointB1].Z + PositionOther.Z > MinBoundsZ &&
			Vertices[PointB1].Z + PositionOther.Z < MaxBoundsZ &&

			Vertices[PointC1].X + PositionOther.X > MinBoundsX &&
			Vertices[PointC1].X + PositionOther.X < MaxBoundsX &&
			Vertices[PointC1].Y + PositionOther.Y > MinBoundsY &&
			Vertices[PointC1].Y + PositionOther.Y < MaxBoundsY &&
			Vertices[PointC1].Z + PositionOther.Z > MinBoundsZ &&
			Vertices[PointC1].Z + PositionOther.Z < MaxBoundsZ)
		{
			NodeVertexCount++;
			indexA1 = indexA1 + 3;
		}


		else
		{
			indexA1 = indexA1 + 3;
		}


	}



}

	
	



void AQuadtree::GenerateEdgeVertices()
{
	for (int i = 0; i < Triangles.Num() / 3; i++)
	{
		GetEdgeVertices(Triangles[indexA3], Triangles[indexB3], Triangles[indexC3]);
	}

	BuildEdgeTriangleBuffer();
	
	
	meshEdges->CreateMeshSection_LinearColor(0, EdgeVertices, EdgeTriangles, Normals, UV0, VertexColors, Tangents, true);	
}

void AQuadtree::GetEdgeVertices(int PointA, int PointB, int PointC)
{

	if (Vertices[PointA].X + PositionOther.X < MinBoundsX &&
		Vertices[PointA].X + PositionOther.X > MaxBoundsX &&
		Vertices[PointA].Y + PositionOther.Y < MinBoundsY &&
		Vertices[PointA].Y + PositionOther.Y > MaxBoundsY &&
		Vertices[PointA].Z + PositionOther.Z < MinBoundsZ &&
		Vertices[PointA].Z + PositionOther.Z > MaxBoundsZ &&

		Vertices[PointB].X + PositionOther.X < MinBoundsX &&
		Vertices[PointB].X + PositionOther.X > MaxBoundsX &&
		Vertices[PointB].Y + PositionOther.Y < MinBoundsY &&
		Vertices[PointB].Y + PositionOther.Y > MaxBoundsY &&
		Vertices[PointB].Z + PositionOther.Z < MinBoundsZ &&
		Vertices[PointB].Z + PositionOther.Z > MaxBoundsZ &&

		Vertices[PointC].X + PositionOther.X < MinBoundsX &&
		Vertices[PointC].X + PositionOther.X > MaxBoundsX &&
		Vertices[PointC].Y + PositionOther.Y < MinBoundsY &&
		Vertices[PointC].Y + PositionOther.Y > MaxBoundsY &&
		Vertices[PointC].Z + PositionOther.Z < MinBoundsZ &&
		Vertices[PointC].Z + PositionOther.Z > MaxBoundsZ)
	{
		EdgeVertices.Add(Vertices[PointA]);
		EdgeVertices.Add(Vertices[PointB]);
		EdgeVertices.Add(Vertices[PointC]);

		indexA3 = indexA3 + 3;
		indexB3 = indexB3 + 3;
		indexC3 = indexC3 + 3;
		
		Vertices.Remove(NodeVertices[0]);
	}
	else
	{
		indexA3 = indexA3 + 3;
		indexB3 = indexB3 + 3;
		indexC3 = indexC3 + 3;
	}
}

void AQuadtree::BuildEdgeTriangleBuffer()
{
	for (int i = 0; i < EdgeVertices.Num(); i++)
	{
		EdgeTriangles.Add(i);
	}
}



void AQuadtree::BuildNormals()
{
	//if (NodeVertices.Num() > 0)
	//{
	//	for (int i = 0; i < Triangles.Num() / 3; i++)
		//{
		//	CalculateNormals(Triangles[indexA4], Triangles[indexB4], Triangles[indexC4]);
		//}
	//}
	


	//for (int i = 0; i < NodeVertices.Num(); i++)
	//{
	//	CalculateNormalsOther();
	//}
}


void AQuadtree::CalculateNormals(int pointA, int pointB, int pointC)
{
	
		FVector p1, p2, p3, u, v, n;
		float nx, ny, nz;

		nx = 0;
		ny = 0;
		nz = 0;

		p1 = Vertices[pointA];
		p2 = Vertices[pointB];
		p3 = Vertices[pointC];
		
		u = p2 - p1;
		v = p3 - p1;
		n = u * v;
		
		nx = u.Y* v.Z - u.Z * v.Y;


		ny = u.Z* v.X - u.X * v.Z;


		nz = u.X * v.Y - u.Y * v.X;

		
		Normals.Add(FVector(nx, ny, nz));

		indexA4 = indexA4 + 3;
		indexB4 = indexB4 + 3;
		indexC4 = indexC4 + 3;

}


void AQuadtree::CalculateNormalsOther()
{
	Normals.Add(FVector(1, 0, 0));
}


void AQuadtree::ResetAllIndexes()
{
	indexA = 0;
	indexB = 1;
	indexC = 2;


	indexA1 = 0;
	indexB1 = 1;
	indexC1 = 2;

	indexA2 = 0;
	indexB2 = 1;
	indexC2 = 2;

	indexA3 = 0;
	indexB3 = 1;
	indexC3 = 2;

	indexA4 = 0;
	indexB4 = 1;
	indexC4 = 2;

	indexA5 = 0;
	indexB5 = 1;
	indexC5 = 2;
}


void AQuadtree::InitialiseParentBounds()
{
	// max bounds x 
	ParentMaxBoundsX = ParentNodePosition.X + ParentNodeBoundsScaleX;


	ParentMinBoundsX = ParentNodePosition.X - ParentNodeBoundsScaleX;


	// max bounds y
	ParentMaxBoundsY = ParentNodePosition.Y + ParentNodeBoundsScaleY;


	ParentMinBoundsY = ParentNodePosition.Y - ParentNodeBoundsScaleY;


	// max bounds z
	ParentMaxBoundsZ = ParentNodePosition.Z + ParentNodeBoundsScaleZ;


	ParentMinBoundsZ = ParentNodePosition.Z - ParentNodeBoundsScaleZ;
}


void AQuadtree::GetParentBounds(float &outParentNodeBounsScaleX, float &outParentNodeBounsScaleY, float &outParentNodeBounsScaleZ, float &outMaxBoundsX, float &outMinBoundsX, float &outMaxBoundsY, float &outMinBoundsY, float &outMaxBoundsZ, float &outMinBoundsZ)
{
	
	outParentNodeBounsScaleX = ParentNodeBoundsScaleX;

	outParentNodeBounsScaleY = ParentNodeBoundsScaleY;

	outParentNodeBounsScaleZ = ParentNodeBoundsScaleZ;
	
	
	
	outMaxBoundsX = ParentMaxBoundsX;
	outMinBoundsX = ParentMinBoundsX;

	outMaxBoundsY = ParentMaxBoundsY;
	outMinBoundsY = ParentMinBoundsY;

	outMaxBoundsZ = ParentMaxBoundsZ;
	outMinBoundsZ = ParentMinBoundsZ;
		
}

void AQuadtree::SetParentBounds(float inParentNodeBounsScaleX, float  inParentNodeBounsScaleY, float  inParentNodeBounsScaleZ, float inMaxBoundsX, float inMinBoundsX, float inMaxBoundsY, float inMinBoundsY, float inMaxBoundsZ, float inMinBoundsZ)
{
	
	ParentNodeBoundsScaleX = inParentNodeBounsScaleX;
	

	ParentNodeBoundsScaleY = inParentNodeBounsScaleY;
	

	ParentNodeBoundsScaleZ = inParentNodeBounsScaleZ;
	
	
	
	ParentMaxBoundsX = inMaxBoundsX;
	ParentMinBoundsX = inMinBoundsX;

	ParentMaxBoundsY = inMaxBoundsY;
	ParentMinBoundsY = inMinBoundsY;

	ParentMaxBoundsZ = inMaxBoundsZ;
	ParentMinBoundsZ = inMinBoundsZ;
}


void AQuadtree::HalfParentNodeBoundsScale(float inParentNodeBounsScaleX, float  inParentNodeBounsScaleY, float  inParentNodeBounsScaleZ)
{
	ParentNodeBoundsScaleX = inParentNodeBounsScaleX / 2;
	

	ParentNodeBoundsScaleY = inParentNodeBounsScaleY / 2;
	

	ParentNodeBoundsScaleZ = inParentNodeBounsScaleZ / 2;
	
}


bool AQuadtree::IsDesiredNodeSize(float MinNodeSize)
{
	if (NodeBoundsScaleX > MinNodeSize &&
		NodeBoundsScaleY > MinNodeSize &&
		NodeBoundsScaleZ > MinNodeSize)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}