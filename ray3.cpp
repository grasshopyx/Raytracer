#include"ray3.h"
//Ray3::Ray3(const Vec3& origin, const Vec3& direction) 	// this needs a new constructor Vec3()
//{
//	this->origin=origin;
//	this->direction=direction;
//}

Vec3 Ray3::getPoint(float t)const
{
	return this->origin.add(this->direction.multiply(t));
}
Vec3 Ray3::getOrigin()const
{
	return origin;
}
Vec3 Ray3::getDirection()const
{
	return direction;
}
