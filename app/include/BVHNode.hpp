#pragma once

#include "AABB.hpp"
#include "Tri.hpp"

class BVHNode
{
public:
	explicit BVHNode(const std::vector<Tri>& triangleList);
	~BVHNode() = default;

private:
	void CreateBounds(std::vector<Tri> triangleList);

	int GetGreatestAxis(const Vector3& extents);/// 0 = x, 1 = y, 2 = z

	using leftRightSplit = std::tuple<std::vector<Tri>, std::vector<Tri>>;
	leftRightSplit CreateSplitLists(int axis, const std::vector<Tri>& list);

private:
	AABB bounds;

	int num_tris{};
	std::vector<Tri*> tris;

	std::unique_ptr<BVHNode> left{ nullptr };
	std::unique_ptr<BVHNode> right{ nullptr };
};

BVHNode::BVHNode(const std::vector<Tri>& triangleList)
{
	CreateBounds(triangleList);
	if (triangleList.size() < 8)/// 8 is arbitrary
	{
		/// make leaf node
		return;
	}
	/// find out how to split the axis
	auto axis = GetGreatestAxis(bounds.extents());

	/// sort into left and right list
	auto [leftList, rightList] = CreateSplitLists(axis, triangleList);

	/// recurse
	left = std::make_unique<BVHNode>(leftList);
	right = std::make_unique<BVHNode>(rightList);
}

void BVHNode::CreateBounds(std::vector<Tri> triangleList)
{
	/// initialise menber bounding box
	bounds = AABB();
	/// create bounding box for all the triangles in the list
	for (auto t : triangleList)
	{
		bounds = AABB::MergeBounds(bounds, t.GetBoundingBox());
	}
}

int BVHNode::GetGreatestAxis(const Vector3& extents)
{
	auto dominant_x = extents.x() > extents.y() && extents.x() > extents.z();
	if (dominant_x) return 0;
	return extents.y() > extents.z() ? 1 : 2;
}

BVHNode::leftRightSplit BVHNode::CreateSplitLists(int axis, const std::vector<Tri>& list)
{
	/// create the new list
	std::vector<Tri> left_list{};
	std::vector<Tri> right_list{};

	/// check if the centre position is greater or lower than the mid point
	for (auto tri : list)
	{
		if (tri.GetBoundingBox().mid().value[axis] < bounds.mid().value[axis])
		{
			left_list.push_back(tri);
			continue;
		}
		right_list.push_back(tri);
	}

	return { left_list, right_list };
}
