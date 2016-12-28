#pragma once

#include <GL/glut.h>

class Vector3
{
public:
	GLfloat x, y, z;

	Vector3(GLfloat x = 0.0f, GLfloat y = 0.0f, GLfloat z = 0.0f)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3 operator+(const Vector3& v) {
		return Vector3(this->x + v.x, this->y + v.y, this->z + v.z);
	}

	Vector3 operator-(const Vector3& v) {
		return Vector3(this->x - v.x, this->y - v.y, this->z - v.z);
	}

	Vector3 operator+(const GLfloat c) {
		return Vector3(this->x + c, this->y + c, this->z + c);
	}

	Vector3 operator-(const GLfloat c) {
		return Vector3(this->x - c, this->y - c, this->z - c);
	}

	void operator+=(const Vector3& v) {
		this->x += v.x;
		this->y += v.y;
		this->z += v.z;
	}

	void operator-=(const Vector3& v) {
		this->x -= v.x;
		this->y -= v.y;
		this->z -= v.z;
	}

	void operator+=(const GLfloat c) {
		this->x += c;
		this->y += c;
		this->z += c;
	}

	void operator-=(const GLfloat c) {
		this->x -= c;
		this->y -= c;
		this->z -= c;
	}

	Vector3 operator*(const Vector3& v) {
		return Vector3(this->x * v.x, this->y * v.y, this->z * v.z);
	}

	Vector3 operator/(const Vector3& v) {
		return Vector3(this->x / v.x, this->y / v.y, this->z / v.z);
	}

	Vector3 operator*(const GLfloat c) {
		return Vector3(this->x * c, this->y * c, this->z * c);
	}

	Vector3 operator/(const GLfloat c) {
		return Vector3(this->x / c, this->y / c, this->z / c);
	}

	void operator*=(const Vector3& v) {
		this->x *= v.x;
		this->y *= v.y;
		this->z *= v.z;
	}

	void operator/=(const Vector3& v) {
		this->x /= v.x;
		this->y /= v.y;
		this->z /= v.z;
	}

	void operator*=(const GLfloat c) {
		this->x *= c;
		this->y *= c;
		this->z *= c;
	}

	void operator/=(const GLfloat c) {
		this->x /= c;
		this->y /= c;
		this->z /= c;
	}
};