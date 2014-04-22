#include"vec3.h"
#include<math.h>
//Vec3::Vec3(float x, float y, float z)
//{
//	this->x=x;
//	this->y=y;
//	this->z=z;	
//}
//Vec3::Vec3()
//{
//}
Vec3& Vec3::copy()
{
	//return Vec3(this->x,this->y,this->z);
	return *this;
}
float Vec3::length()const
{
	return sqrt(this->x*this->x+this->y*this->y+this->z*this->z);
}
float Vec3::sqLength()const
{
	return this->x*this->x+this->y*this->y+this->z*this->z;
}
Vec3 Vec3::normalize()const
{
	float inv=1/length();
	return Vec3(this->x*inv,this->y*inv,this->z*inv);
}
Vec3 Vec3::negate()const
{
	return Vec3(-this->x,-this->y,-this->z);
}
Vec3 Vec3::add(const Vec3 &vec)const
{
	return Vec3(this->x+vec.x,this->y+vec.y,this->z+vec.z);
}

Vec3 Vec3::substract(const Vec3 &vec)const
{
	return Vec3(this->x-vec.x,this->y-vec.y,this->z-vec.z);
}
Vec3 Vec3::multiply(const float f)const
{
	return Vec3(this->x*f,this->y*f,this->z*f);
}
Vec3 Vec3::divide(const float f)const
{
	float invf=1/f;
	return Vec3(this->x*invf,this->y*invf,this->z*invf);
}

float Vec3::dot(const Vec3& vec)const
{
	return this->x*vec.x+this->y*vec.y+this->z*vec.z;
}
Vec3 Vec3::cross(const Vec3& vec)const
{
	return Vec3(-this->z*vec.y+this->y*vec.z,this->z*vec.x-this->x*vec.z,-this->y*vec.x+this->x*vec.y);
}

float Vec3::getx()const
{
	return x;
}
		
float Vec3::gety()const
{
	return y;
}
float Vec3::getz()const
{
	return z;
}
const Vec3 Vec3::zero=Vec3(0,0,0); 	// even if zero is private, this def is ok
//
//Vec3::Vec3(const Vec3&vec){
//	x=vec.x;
//	y=vec.y;
//	z=vec.z;
//}

