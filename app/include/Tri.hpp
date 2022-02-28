#pragma once

#include <array>

#include "Vector3.hpp"

struct Hit;
class AABB;
class Ray;

class Tri
{
public:
	using Normals = std::array<Vector3, 3>;
	using Vertices = std::array<Vector3, 3>;

public:
	Tri(Vertices v, Normals n) : vertices(v), normals(n) {}
	~Tri() = default;

public:
	bool hit(const Ray& ray, Hit& hit);
	const AABB getBoundingBox();

	inline Vertices& GetVertices() { return vertices; }
	inline Normals& GetNormals() { return normals; }
	inline Vector3 GetFaceNormal() { return (normals[0] + normals[1] + normals[2]) / 3; }

private:
	Normals normals;  /// i want to store this in contiguous memory...
	Vertices vertices;/// i want to store this in contiguous memory...
};
