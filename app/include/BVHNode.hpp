#pragma once

#include "AABB.hpp"
#include "Hit.hpp"
#include "Math.hpp"
#include "Tri.hpp"
#include <algorithm>

class BVHNode
{
public:
	explicit BVHNode(const std::vector<Tri>& triangleList);
	~BVHNode() = default;

	bool hit(const Ray& ray, Hit& hit);

private:
	void CreateBounds(const std::vector<Tri>& triangleList);
	void makeLeaf(const std::vector<Tri>& triangleList);
	static int GetGreatestAxis(const Vector3& extents);/// 0 = x, 1 = y, 2 = z

	using leftRightSplit = std::tuple<std::vector<Tri>, std::vector<Tri>>;
	leftRightSplit CreateSplitLists(int axis, const std::vector<Tri>& list);
	leftRightSplit CreateSplitListsSAH(int axis, std::vector<Tri>& list);

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

	/// todo remove ??
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

bool BVHNode::hit(const Ray& ray, Hit& hit)
{
	/// ont draw if you dont hit
	if (!bounds.hit(ray, 0, 999)) return false;

	/// check if leaf
	if (!is_leaf)
	{
		/// hit recursive
		auto l = left->hit(ray, hit);
		auto r = right->hit(ray, hit);
		return l || r;
	}

	/// add triangles to list
	for (auto t : tris)
	{
		t.hit(ray, hit);
		//tri_list.push_back(t);
	}
	return true;
}

BVHNode::leftRightSplit BVHNode::CreateSplitListsSAH(int axis, std::vector<Tri>& list)
{
	/// create the new lists
	std::vector<Tri> left_list{};
	std::vector<Tri> right_list{};

	/// Partition primitives using approximate SAH
	/// todo : remove? : i dont think i need this first bit
	/*	if (list.size() <= max_tris)
	{
		/// todo : Partition primitives into equally sized subsets
		/// sort based on tri.mid() < tri.mid()
		auto mid = list.begin() + list.size() / 2;
		std::sort(list.begin(),list.end(), [axis](Tri a, Tri b)
				  { return a.GetAABB().midpoint().value[axis] < a.GetAABB().midpoint().value[axis]; });
		for(auto i = list.begin(); i < mid; i++) left_list.emplace_back(*i);
		for(auto i = mid; i < list.end(); i++) right_list.emplace_back(*i);
		/// return the lists
		return { left_list, right_list };
	}*/

	/// todo : Allocate BucketInfo for SAH partition buckets
	constexpr auto bucket_count = 8;
	struct Bucket {
		int count = 0;
		AABB bounds;
	};
	std::array<Bucket, bucket_count> bucket_list;

	/// todo : Initialize BucketInfo for SAH partition buckets

	for (auto itr = list.begin(); itr < list.end(); ++itr)
	{
		/// Sections the triangles into buckets based on their offset from the min point of the AAbb
		///int b = bucket_count * bounds.Offset(itr->GetAABB().midpoint().value[axis]);
		int b = static_cast<int>(bucket_count) * (bounds.min() - itr->GetAABB().midpoint()).value[axis];
		if (b == bucket_count) b = bucket_count - 1;
		bucket_list[b].count++;
		bucket_list[b].bounds = AABB::MergeBounds(bucket_list[b].bounds, itr->GetAABB());
	}

	/// todo : Compute costs for splitting after each bucket
	/// store the cost for each bucket
	float cost[bucket_count - 1];

	for (int i = 0; i < bucket_count - 1; ++i)
	{
		/// use the first value to prevent merging with {}
		AABB b0 = bucket_list[0].bounds;
		AABB b1 = bucket_list[0].bounds;

		int count0 = 0;
		int count1 = 0;

		for (int j = 0; j <= i; ++j)
		{
			b0 = AABB::MergeBounds(b0, bucket_list[j].bounds);
			count0 += bucket_list[j].count;
		}

		for (int j = i + 1; j < bucket_count; ++j)
		{
			b1 = AABB::MergeBounds(b1, bucket_list[j].bounds);
			count1 += bucket_list[j].count;
		}

		/// work out the cost based on the surface area
		cost[i] = .125f + (count0 * b0.surfaceArea() + count1 * b1.surfaceArea()) / bounds.surfaceArea();
	}
	/// todo : Find bucket to split at that minimizes SAH metric

	/// todo : Either create leaf or split primitives at selected SAH bucket


	return { left_list, right_list };
}
