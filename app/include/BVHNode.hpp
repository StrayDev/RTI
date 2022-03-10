#pragma once

#include "AABB.hpp"

class BVHNode
{
public:
	explicit BVHNode(AABB bounds) : bounding_box(bounds)  {};
	~BVHNode() = default;

	AABB& GetBoundingBox() { return bounding_box; }

private:
	bool is_leaf = false;
	AABB bounding_box;

	BVHNode* left = nullptr;
	BVHNode* right = nullptr;
};
