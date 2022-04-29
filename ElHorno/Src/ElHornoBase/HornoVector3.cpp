#include "HornoVector3.h"
#include <math.h>       /* sqrt */

namespace El_Horno {
	/*HornoVector3::HornoVector3(float x, float y, float z) : x_(x), y_(y), z_(z) {}

	HornoVector3::HornoVector3() : x_(0), y_(0), z_(0) {}*/

	float HornoVector3::magnitude()
	{
		return sqrtf(x_*x_ + y_*y_ + z_*z_);
	}

	HornoVector3 HornoVector3::normalized()
	{
		float m = magnitude();
		if(m != 0)
			return HornoVector3(x_, y_, z_) / m;
		return HornoVector3(x_, y_, z_);
	}

	void HornoVector3::normalize()
	{
		float m = magnitude();
		if (m != 0) {
			x_ /= m;
			y_ /= m;
			z_ /= m;
		}
	}

	HornoVector3 El_Horno::HornoVector3::operator+(const HornoVector3& b)
	{
		return HornoVector3({ this->x_ + b.x_, this->y_ + b.y_, this->z_ + b.z_ });
	}
	HornoVector3 HornoVector3::operator-(const HornoVector3& b)
	{
		return HornoVector3({ this->x_ - b.x_, this->y_ - b.y_, this->z_ - b.z_ });
	}
	
	HornoVector3 HornoVector3::operator+(float b)
	{
		return HornoVector3({ this->x_ + b, this->y_ + b, this->z_ + b });
	}
	HornoVector3 HornoVector3::operator-(float b)
	{
		return HornoVector3({ this->x_ - b, this->y_ - b, this->z_ - b });
	}
	HornoVector3 HornoVector3::operator*(float b)
	{
		return HornoVector3({ this->x_ * b, this->y_ * b, this->z_ * b });
	}

	HornoVector3 HornoVector3::operator/(float b)
	{
		return HornoVector3({ this->x_ / b, this->y_ / b, this->z_ / b });
	}

	HornoVector3 HornoVector3::dot(const HornoVector3& other)
	{
		return HornoVector3(x_ * other.x_, y_ * other.y_, z_ * other.z_);
	}

	HornoVector3 HornoVector3::cross(const HornoVector3& other)
	{
		return HornoVector3(y_ * other.z_ - z_ * other.y_,
							x_ * other.z_ - z_ * other.x_,
							x_ * other.x_ - y_ * other.x_);
	}

	void HornoVector3::operator+=(const HornoVector3& b)
	{
		this->x_ + b.x_; this->y_ + b.y_; this->z_ + b.z_;
	}
	void HornoVector3::operator-=(const HornoVector3& b)
	{
		this->x_ - b.x_; this->y_ - b.y_; this->z_ - b.z_;
	}

	void HornoVector3::operator+=(float b)
	{
		this->x_ + b; this->y_ + b; this->z_ + b;
	}
	void HornoVector3::operator-=(float b)
	{
		this->x_ - b; this->y_ - b; this->z_ - b;
	}
	void HornoVector3::operator*=(float b)
	{
		this->x_ * b; this->y_ * b; this->z_ * b;
	}
	void HornoVector3::operator/=(float b)
	{
		this->x_ / b; this->y_ / b; this->z_ / b;
	}

	bool HornoVector3::operator==(const HornoVector3& b)
	{
		return (this->x_ == b.x_ && this->y_ == b.y_ && this->z_ == b.z_);
	}
	bool HornoVector3::operator!=(const HornoVector3& b)
	{
		return !(this == &b);
	}
}
