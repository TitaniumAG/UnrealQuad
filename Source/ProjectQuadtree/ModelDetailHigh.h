#pragma once

#include "ProceduralMeshComponent.h"

class ModelDetailHigh
{
public:
	ModelDetailHigh();
	~ModelDetailHigh();

	// High quality vars
	TArray<FVector> Vertices_High;
	TArray<int> Triangles_High;
	TArray<FVector> Normals_High;
	TArray<FProcMeshTangent> Tangents_High;
	TArray<FVector2D> UV0_High;
	TArray<FLinearColor>VertexColors_High;
};

