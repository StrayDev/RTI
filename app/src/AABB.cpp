#include "AABB.hpp"

bool AABB::hit(const Ray& r, double t_min, double t_max) const
{
	/// from Andrew Kensler at Pixar
	for (int a = 0; a < 3; a++)
	{
		auto invD = 1.0f / r.getDirection().value[a];
		auto t0 = (min().value[a] - r.getOrigin().value[a]) * invD;
		auto t1 = (max().value[a] - r.getOrigin().value[a]) * invD;

		if (invD < 0.0f)
		{
			std::swap(t0, t1);
		}

		t_min = t0 > t_min ? t0 : t_min;
		t_max = t1 < t_max ? t1 : t_max;

		if (t_max <= t_min)
		{
			return false;
		}
	}
	return true;
}

AABB AABB::MergeBounds(AABB box1, AABB box2)
{
	auto small = Vector3{
		fmin(box1.min().x(), box2.min().x()),
		fmin(box1.min().y(), box2.min().y()),
		fmin(box1.min().z(), box2.min().z())
	};

	auto large = Vector3{
		fmax(box1.max().x(), box2.max().x()),
		fmax(box1.max().y(), box2.max().y()),
		fmax(box1.max().z(), box2.max().z())
	};

	return { small, large };
}
