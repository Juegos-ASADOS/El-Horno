#include "HornoVector3.h"

namespace El_Horno {
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
