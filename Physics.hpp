#pragma once

#include "Tri.hpp"
#include "Vector3.hpp"

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

	static bool raycast(const Ray& ray, const Hit& hit, const Tri& tri)
	{
		/// get the plane's normal and nDot
		auto normal = GetNormal(tri);
		auto normalDirectionDot = Vector3::dot(normal, ray.getDirection());

		/// check for parallel lines edge case
		if (fabs(normalDirectionDot) < epsilon)
		{
			return false;
		}

		/// get the oDot
		auto normalOriginDot = Vector3::dot(normal, ray.getOrigin());

		/// P is the point on the plane
		/// Point = Origin + ( t * Direction )
		auto D = -Vector3::dot(normal, tri[0]);
		auto t = -(normalOriginDot + D) / normalDirectionDot;
		if (t < 0) return false;/// tri is behind the ray
		auto P = ray.getOrigin() + t * ray.getDirection();

		/// check that P is inside the triangle
		auto edge = tri[1] - tri[0];
		auto vp = P - tri[0];
		auto C = Vector3::cross(edge, vp);
		if (Vector3::dot(normal, C) < 0) return false;

		edge = tri[2] - tri[1];
		vp = P - tri[1];
		C = Vector3::cross(edge, vp);
		if (Vector3::dot(normal, C) < 0) return false;

		edge = tri[0] - tri[2];
		vp = P - tri[2];
		C = Vector3::cross(edge, vp);
		if (Vector3::dot(normal, C) < 0) return false;

		/// the ray hits the triangle
		return true;
	}

}// namespace Physics
