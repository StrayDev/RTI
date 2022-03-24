#pragma once

#include <array>

#include "Vector3.hpp"
#include "AABB.hpp"

struct Hit;
class Ray;

class Tri
{
public:
	using Normals = std::array<Vector3, 3>;
	using Vertices = std::array<Vector3, 3>;

public:
	Tri(Vertices v, Normals n) : vertices(v), normals(n) {}
/*	{
		bounding_box = GetBounds();
	}*/
	~Tri() = default;

public:
	bool hit(const Ray& ray, Hit& hit);
	AABB GetBounds() const;

	//inline const AABB GetAABB() const { return GetBounds(); }
	Vertices& GetVertices() { return vertices; }
	Normals& GetNormals() { return normals; }
	inline Vector3 GetFaceNormal();
	inline Vector3 GetHitNormal(double u, double v);

private:
	Normals normals;  /// i want to store this in contiguous memory...
	Vertices vertices;/// i want to store this in contiguous memory...
	AABB bounding_box;
};
