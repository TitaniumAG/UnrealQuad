#pragma once

#include "ProceduralMeshComponent.h"

class ModelDetailMedium
{
public:
	ModelDetailMedium();
	~ModelDetailMedium();


	// medium quality vars
	TArray<FVector> Vertices_Medium;
	TArray<int> Triangles_Medium;
	TArray<FVector> Normals_Medium;
	TArray<FProcMeshTangent> Tangents_Medium;
	TArray<FVector2D> UV0_Medium;
	TArray<FLinearColor>VertexColors_Medium;
};

