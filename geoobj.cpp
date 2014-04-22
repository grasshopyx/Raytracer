#include"geoobj.h"
#include"math.h"
#include"limits.h"
#include<iostream>
using namespace std;

//IntersectResult::IntersectResult()
//{
//	this->geometry=Null;
//	this->distance=0;
//	this->position=Vec3::zero;
//	this->normal=Vec3::zero;
//}

void IntersectResult::setGeometry(Object* rhs)
{
	geometry=rhs;
}
void IntersectResult::setDistance(float rhs)
{
	distance=rhs;
}
void IntersectResult::setPosition(const Vec3& rhs)
{
	position=rhs;
}
void IntersectResult::setNormal(const Vec3& rhs)
{
	normal=rhs;
}

IntersectResult Sphere::intersect(Ray3 ray)
{
	Vec3 v = ray.getOrigin().substract(this->center);
	float a0 = v.sqLength() - this->sqRadius;
	float DdotV = ray.getDirection().dot(v);

	if(DdotV <= 0)
	{
		float discr = DdotV * DdotV - a0;
		if(discr >=0)
		{
			IntersectResult result = IntersectResult();
			result.setGeometry(this);
			//result.setGeometry(SPHERE);
			result.setDistance(-DdotV-sqrt(discr));
			result.setPosition(ray.getPoint(result.getDistance()));
			result.setNormal(result.getPosition().substract(center).normalize());
			return result;
		}
	}
	return IntersectResult(); 	// noHit
}


Sphere::Sphere(const Vec3& center, const float radius, Material* mat) 	// I can't write material(mat) here. It may be a bug of g++. It can't initialize a member from base class.
{
	this->material=mat;
	//material(mat)
	this->center=center;
	this->radius=radius;
	this->sqRadius=radius*radius;
	//this->material=material;
}
Plane::Plane(const Vec3& norm, const float dis, Material* mat):normal(norm),distance(dis)
{
	material=mat;
	position=normal.multiply(distance);	// why without "position=...", the result is the same?
}


IntersectResult Plane::intersect(Ray3 ray)
{
	float a = ray.getDirection().dot(normal);
	if ( a >= 0 )
		return IntersectResult();

	float b = normal.dot(ray.getOrigin().substract(position));

	IntersectResult result = IntersectResult();
	result.setGeometry(this);
	//result.setGeometry(PLANE);
	result.setDistance(-b/a);
	result.setPosition(ray.getPoint(result.getDistance()));
	result.setNormal(normal);
	return result;
}
IntersectResult Union::intersect(Ray3 ray)
{
	int minDistance = INT_MAX;
	IntersectResult minResult = IntersectResult();
	for( int i = 0; i<objects.size();i++)
	{
		IntersectResult result = objects[i]->intersect(ray);
		if(result.getGeometry() && result.getDistance() < minDistance)
		{
			minDistance = result.getDistance();
			minResult = result;
		}

	}
	//cout<<minResult.getGeometry()->material->getReflectiveness()<<endl;
	return minResult;
	
}
