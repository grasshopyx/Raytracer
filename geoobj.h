#ifndef GEOOBJ_H
#define GEOOBJ_H
#include<stdlib.h>
#include"vec3.h"
#include"ray3.h"
#include"material.h"
#include<vector>
using namespace std;
enum object_type{Null,SPHERE,PLANE};

class Object;
class IntersectResult
{
	private:
		//enum object_type geometry;
		Object *geometry;
		float distance;
		Vec3 position;
		Vec3 normal;
	public:
		IntersectResult():geometry(NULL),distance(0),position(Vec3::zero),normal(Vec3::zero){}
		void setGeometry(Object*);
		void setDistance(float);
		void setPosition(const Vec3&);
		void setNormal(const Vec3&);
		Object* getGeometry()const{return geometry;}
		float getDistance()const{return distance;}
		Vec3& getPosition()
		{
			return position;
		}
		Vec3& getNormal()
		{
			return normal;
		}
};

class Object
{
	public:
		virtual IntersectResult intersect(Ray3 ray)=0;
	//protected:
//		Material &material; 	// i don't know why i can't do this here. maybe a bug

		Material *material;

		//int a;

};

class Sphere:public Object
{
	private:
		Vec3 center;
		float radius;
		float sqRadius;
		//Material &material;
	public:
		Sphere(const Vec3&, const float, Material*);
		//Sphere(Vec3,float);
		IntersectResult intersect(Ray3 ray);
};
class Plane:public Object
{
	private:
		Vec3 normal;
		float distance;
		Vec3 position;
		//Material &material;
	public:
		//Plane(){position=normal.multiply(distance);}
		Plane(const Vec3& norm, const float dis, Material* mat);

		IntersectResult intersect(Ray3 ray);
};

class Union:public Object
{
	public:
		vector<Object *> objects;
		IntersectResult intersect(Ray3 ray);
};
#endif
