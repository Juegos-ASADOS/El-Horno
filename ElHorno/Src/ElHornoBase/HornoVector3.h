#pragma once
#ifndef _HORNOVECTOR3_H
#define _HORNOVECTOR3_H

#include <iostream>
namespace El_Horno {
	class _declspec(dllexport) HornoVector3
	{
	public:
		HornoVector3(float x, float y, float z) : x_(x), y_(y), z_(z) {};
		HornoVector3() : x_(0), y_(0), z_(0) {};

		float magnitude();

		void normalize();
		HornoVector3 normalized();

		HornoVector3 operator+(const HornoVector3 & b);
		HornoVector3 operator-(const HornoVector3 & b);

		HornoVector3 operator+(float b);
		HornoVector3 operator-(float b);
		HornoVector3 operator*(float b);
		HornoVector3 operator/(float b);

		HornoVector3 dot(const HornoVector3& other);
		HornoVector3 cross(const HornoVector3& other);

		void operator+=(const HornoVector3& b);
		void operator-=(const HornoVector3& b);

		void operator+=(float b);
		void operator-=(float b);
		void operator*=(float b);
		void operator/=(float b);

		bool operator==(const HornoVector3& b);
		bool operator!=(const HornoVector3& b);
		
		friend std::ostream& operator<<(std::ostream& os, const HornoVector3& vector);
		friend std::istream& operator>> (std::istream& in, HornoVector3& vector);

		float x_, y_, z_;
	};
}
#endif _HORNOVECTOR3_H