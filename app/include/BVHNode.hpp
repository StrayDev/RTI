#pragma once

#include "AABB.hpp"
#include "Hit.hpp"
#include "Math.hpp"
#include "Tri.hpp"

class BVHNode
{
public:
	explicit BVHNode(const std::vector<Tri>& triangleList);
	~BVHNode() = default;

	bool hit(const Ray& ray, std::vector<Tri>& tri_list);

private:
	void CreateBounds(const std::vector<Tri>& triangleList);
	void makeLeaf(const std::vector<Tri>& triangleList);
	static int GetGreatestAxis(const Vector3& extents);/// 0 = x, 1 = y, 2 = z

	using leftRightSplit = std::tuple<std::vector<Tri>, std::vector<Tri>>;
	leftRightSplit CreateSplitLists(int axis, const std::vector<Tri>& list);

private:
	/// 8 is arbitrary
	const int max_tris = 8;

	AABB bounds;
	bool is_leaf{ false };

	std::vector<Tri> tris{};

	std::unique_ptr<BVHNode> left{ nullptr };
	std::unique_ptr<BVHNode> right{ nullptr };
};

BVHNode::BVHNode(const std::vector<Tri>& triangleList)
{
	/// create the bounds
	CreateBounds(triangleList);

	/// create if node
	if (triangleList.size() <= max_tris)
	{
		makeLeaf(triangleList);
		return;
	}

	/// find out how to split the axis
	auto axis = GetGreatestAxis(bounds.extents());
	auto [left_list, right_list] = CreateSplitLists(axis, triangleList);

	/// catch one sided loop
	if (left_list.empty() || right_list.empty())
	{
		std::cout << "Could not separate : " << left_list.size() << ' ' << right_list.size() << '\n';
		makeLeaf(triangleList);
		return;
	}

	/// recurse
	left = std::make_unique<BVHNode>(left_list);
	right = std::make_unique<BVHNode>(right_list);
}

void BVHNode::makeLeaf(const std::vector<Tri>& triangleList)
{
	/// make leaf node
	is_leaf = true;

	for (auto tri : triangleList)
	{
		tris.push_back(tri);
	}
}

void BVHNode::CreateBounds(const std::vector<Tri>& triangleList)
{
	/// create bounding box for all the triangles in the list
	bounds = triangleList.back().GetAABB();
	for (auto t : triangleList)
	{
		bounds = AABB::MergeBounds(bounds, t.GetAABB());
	}
}

int BVHNode::GetGreatestAxis(const Vector3& extents)
{
	auto x_abs = fabs(extents.x());
	auto y_abs = fabs(extents.y());
	auto z_abs = fabs(extents.z());

	if (x_abs > y_abs && x_abs > z_abs) return 0;
	return y_abs > z_abs ? 1 : 2;
}

BVHNode::leftRightSplit BVHNode::CreateSplitLists(int axis, const std::vector<Tri>& list)
{
	/// create the new list
	std::vector<Tri> left_list{};
	std::vector<Tri> right_list{};

	/// store the midpoint
	auto midpoint = bounds.midpoint().value[axis];

	/// todo remove
	auto left_max = -9999.f;
	auto right_min = 9999.f;

	/// check if the mid position is greater or lower than the mid point
	for (auto tri : list)
	{
		auto triMidpoint = tri.GetAABB().midpoint().value[axis];

		if (triMidpoint <= midpoint - epsilon)
		{
			left_max = triMidpoint > left_max ? triMidpoint : left_max;
			left_list.push_back(tri);
			continue;
		}
		right_min = triMidpoint < right_min ? triMidpoint : right_min;
		right_list.push_back(tri);
	}

	return { left_list, right_list };
}

bool BVHNode::hit(const Ray& ray, std::vector<Tri>& tri_list)
{
	/// ont draw if you dont hit
	if (!bounds.hit(ray, 0, 999)) return false;

	/// check if leaf
	if (!is_leaf)
	{
		/// hit recursive
		auto l = left->hit(ray, tri_list);
		auto r = right->hit(ray, tri_list);
		return l || r;
	}

	/// add triangles to list
	for (auto t : tris)
	{
		tri_list.push_back(t);
	}
	return true;
}
