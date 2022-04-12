#pragma once
#ifndef _HORNOVECTOR3_H
#define _HORNOVECTOR3_H

namespace El_Horno {
	class _declspec(dllexport) HornoVector3
	{
	public:
		HornoVector3(float x, float y, float z);
		HornoVector3();

		float x_, y_, z_;

		HornoVector3 operator+(const HornoVector3 & b);
		HornoVector3 operator-(const HornoVector3 & b);

		HornoVector3 operator+(float b);
		HornoVector3 operator-(float b);
		HornoVector3 operator*(float b);
		HornoVector3 operator/(float b);

		void operator+=(const HornoVector3& b);
		void operator-=(const HornoVector3& b);

		void operator+=(float b);
		void operator-=(float b);
		void operator*=(float b);
		void operator/=(float b);

		bool operator==(const HornoVector3& b);
		bool operator!=(const HornoVector3& b);
	};
}
#endif _HORNOVECTOR3_H