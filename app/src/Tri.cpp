#include "Tri.hpp"

#include "Hit.hpp"
#include "Math.hpp"
#include "Ray.hpp"

bool Tri::hit(const Ray& ray, Hit& hit)
{
	/// Möller–Trumbore algorithm
	auto edge1 = vertices[1] - vertices[0];
	auto edge2 = vertices[2] - vertices[0];
	auto h = Vector3::cross(ray.getDirection(), edge2);
	auto a = Vector3::dot(edge1, h);

	if (a > -epsilon && a < epsilon) return false;

	auto f = 1.0 / a;
	auto s = ray.getOrigin() - vertices[0];
	auto u = f * Vector3::dot(s, h);

	if (u < 0.0 || u > 1.0) return false;

	auto q = Vector3::cross(s, edge1);
	auto v = f * Vector3::dot(ray.getDirection(), q);

	if (v < 0.0 || u + v > 1.0) return false;

	auto t = f * Vector3::dot(edge2, q);

	if (t > epsilon && t < hit.t)
	{
		hit.t = t;
		hit.point = ray.getOrigin() + ray.getDirection() * t;
		hit.color = GetFaceNormal();
		return true;
	}
	return false;
}

AABB Tri::CreateAABB()/// this seems really slow
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

/// old triangle intersection code
/*	/// get tri data
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

return true;*/
