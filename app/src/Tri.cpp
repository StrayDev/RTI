#include "Tri.hpp"

#include "AABB.hpp"
#include "Hit.hpp"
#include "Math.hpp"
#include "Ray.hpp"

bool Tri::hit(const Ray& ray, Hit& hit)
{
	/// get tri data
	auto normal = GetFaceNormal();

	/// get the plane's normal and nDot
	auto normalDirectionDot = Vector3::dot(normal, ray.getDirection());

	/// check for parallel lines edge case
	if (fabs(normalDirectionDot) < epsilon) return false;

	/// get the oDot
	auto normalOriginDot = Vector3::dot(normal, ray.getOrigin());

	/// P is the point on the plane
	/// Point = Origin + ( t * Direction )
	auto D = -Vector3::dot(normal, vertices[0]);
	auto t = -(normalOriginDot + D) / normalDirectionDot;

	/// tri is behind the ray
	if (t < 0) return false;
	auto P = ray.getOrigin() + t * ray.getDirection();

	/// check that P is inside the triangle
	auto edge = vertices[1] - vertices[0];
	auto vp = P - vertices[0];
	auto C = Vector3::cross(edge, vp);
	if (Vector3::dot(normal, C) < 0) return false;

	edge = vertices[2] - vertices[1];
	vp = P - vertices[1];
	C = Vector3::cross(edge, vp);
	if (Vector3::dot(normal, C) < 0) return false;

	edge = vertices[0] - vertices[2];
	vp = P - vertices[2];
	C = Vector3::cross(edge, vp);
	if (Vector3::dot(normal, C) < 0) return false;

	/// the ray hits the triangle
	if (t < hit.t)
	{
		hit.t = t;
		hit.color = normal;
	}

	return true;
}

const AABB Tri::getBoundingBox()/// this seems really slow
{
	auto small = Vector3{
		fmin(vertices[0].x(), fmin(vertices[1].x(), vertices[2].x())),
		fmin(vertices[0].y(), fmin(vertices[1].y(), vertices[2].y())),
		fmin(vertices[0].z(), fmin(vertices[1].z(), vertices[2].z())),
	};

	auto large = Vector3{
		fmax(vertices[0].x(), fmax(vertices[1].x(), vertices[2].x())),
		fmax(vertices[0].y(), fmax(vertices[1].y(), vertices[2].y())),
		fmax(vertices[0].z(), fmax(vertices[1].z(), vertices[2].z())),
	};

	return AABB{ small, large };
}
