#pragma once

#include <vector>

#include "Tri.hpp"
#include "Math.hpp"

namespace Physics
{
	class Ray
	{
	public:
		Ray(const Vector3& origin, const Vector3& direction)
			: _origin(origin), _direction(direction) {}

		~Ray() = default;

	public:
		[[nodiscard]] Vector3 getOrigin() const { return _origin; }
		[[nodiscard]] Vector3 getDirection() const { return _direction; }

	private:
		Vector3 _origin;
		Vector3 _direction;
	};

	class Hit
	{

	};

	// Todo : compare this when inlined
	static bool raycast(const Ray& ray, const Hit& hit, const std::vector<Tri>& triList)
	{
		/// keep track of the closest t value
		auto closest = infinity;

		for(auto tri : triList)
		{
			/// get the plane's normal and nDot
			auto normal = GetNormal(tri); //TODO : if we have the normal it will be faster
			auto normalDirectionDot = Vector3::dot(normal, ray.getDirection());

			/// check for parallel lines edge case
			if (fabs(normalDirectionDot) < epsilon) continue;

			/// get the oDot
			auto normalOriginDot = Vector3::dot(normal, ray.getOrigin());

			/// P is the point on the plane
			/// Point = Origin + ( t * Direction )
			auto D = -Vector3::dot(normal, tri[0]);
			auto t = -(normalOriginDot + D) / normalDirectionDot;

			/// tri is behind the ray
			if (t < 0) continue;
			auto P = ray.getOrigin() + t * ray.getDirection();

			/// check that P is inside the triangle
			auto edge = tri[1] - tri[0];
			auto vp = P - tri[0];
			auto C = Vector3::cross(edge, vp);
			if (Vector3::dot(normal, C) < 0) continue;

			edge = tri[2] - tri[1];
			vp = P - tri[1];
			C = Vector3::cross(edge, vp);
			if (Vector3::dot(normal, C) < 0) continue;

			edge = tri[0] - tri[2];
			vp = P - tri[2];
			C = Vector3::cross(edge, vp);
			if (Vector3::dot(normal, C) < 0) continue;

			/// the ray hits the triangle
			if(t < closest)
			{
				closest = t;
				///todo update hit&
			}
		}

		// tells us that a ray has hit
		//std::cout << closest;
		return closest < infinity;
	}

}// namespace Physics
