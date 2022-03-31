#pragma once

#include <vector>
#include "AABB.hpp"
#include "glm/mat4x4.hpp"
#include "Tri.hpp"

class Object
{
public:
	Object() = default;
	~Object() = default;

	void SetPosition(Vector3 pos)
	{
		position = pos;
		for(auto& t : triangles)
		{
			for(auto& v : t.GetVertices())
			{
				v += pos;
			}
		}
	}

public:
	AABB aabb;
	Vector3 position = {0,0,0};
	std::vector<Tri> triangles;

private:


};
