#pragma once

#include "cmath"
#include <array>
#include <iostream>

class Vector3
{
public:
	Vector3(double x, double y, double z)
	{
		value[0] = x;
		value[1] = y;
		value[2] = z;
	}

	Vector3() = default;
	~Vector3() = default;

	//public:
	[[nodiscard]] double x() const { return value[0]; }
	[[nodiscard]] double y() const { return value[1]; }
	[[nodiscard]] double z() const { return value[2]; }

	static inline Vector3 cross(const Vector3& u, const Vector3& v)
	{
		return Vector3{ u.value[1] * v.value[2] - u.value[2] * v.value[1],
						u.value[2] * v.value[0] - u.value[0] * v.value[2],
						u.value[0] * v.value[1] - u.value[1] * v.value[0] };
	}

	[[nodiscard]] inline double length() const;
	[[nodiscard]] inline double lengthSquared() const;

	[[nodiscard]] Vector3 normalize() const;

public:
	std::array<double, 3> value{ 0, 0, 0 };
};

inline std::ostream& operator<<(std::ostream& out, const Vector3& v)
{
	return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

/// negative
inline Vector3 operator-(const Vector3& rhs)
{
	return { -rhs.x(), -rhs.y(), -rhs.z() };
}

/// minus
inline Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
{
	return { lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z() };
}

/// plus
inline Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
{
	return { lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z() };
}

/// minus equals
inline Vector3& operator-=(Vector3& lhs, Vector3& rhs)
{
	lhs.value[0] -= rhs.x();
	lhs.value[1] -= rhs.y();
	lhs.value[2] -= rhs.z();
	return lhs;
}

/// plus equals
inline Vector3& operator+=(Vector3& lhs, Vector3& rhs)
{
	lhs.value[0] += rhs.x();
	lhs.value[1] += rhs.y();
	lhs.value[2] += rhs.z();
	return lhs;
}

/// times
inline Vector3 operator*(const double& value, const Vector3& vector3)
{
	return { vector3.x() * value, vector3.y() * value, vector3.z() * value };
}

inline Vector3 operator*(const Vector3& vector3, const double& value)
{
	return { vector3.x() * value, vector3.y() * value, vector3.z() * value };
}

/// divide
inline Vector3 operator/(const double& value, const Vector3& vector3)
{
	return { vector3.x() / value, vector3.y() / value, vector3.z() / value };
}

inline Vector3 operator/(const Vector3& vector3, const double& value)
{
	return { vector3.x() / value, vector3.y() / value, vector3.z() / value };
}

/// times equals
inline Vector3& operator*=(Vector3& vector3, const double value)
{
	vector3.value[0] *= value;
	vector3.value[1] *= value;
	vector3.value[2] *= value;
	return vector3;
}

/// divide equals
inline Vector3& operator/=(Vector3& vector3, const double value)
{
	return vector3 *= 1 / value;
}
