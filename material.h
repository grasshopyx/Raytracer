#ifndef MATERIAL_H
#define MATERIAL_H
#include "vec3.h"
#include "ray3.h"
#include "color.h"
class Material
{
	public:
		virtual Color sample(const Ray3& ray, const Vec3& position, const Vec3& normal) = 0;
		float getReflectiveness()const{return reflectiveness;}
	protected:
		float reflectiveness;
};
class Wall:public Material
{
	public:
		Wall(float r){reflectiveness=r;}
		Color sample(const Ray3& ray, const Vec3& position, const Vec3& normal){return Color::white;}

};
class CheckMaterial:public Material
{
	private:
		float scale;
		//float reflectiveness;
	public:
		CheckMaterial(float s, float r):scale(s)
		{
			reflectiveness=r;
		}
		CheckMaterial():scale(0.1){reflectiveness=1;}
		Color sample(const Ray3& ray, const Vec3& position, const Vec3& normal);
};
class PhongMaterial:public Material
{
	private:
		Color diffuse,specular;
		float shininess;//reflectiveness;
		//float reflectiveness;
	public:
		PhongMaterial()
		{
			diffuse=Color::white;
			specular=Color::white;
			shininess=16;
			reflectiveness=1;
		}
		PhongMaterial(Color dif, Color spec, float shi, float refl):diffuse(dif), specular(spec), shininess(shi){reflectiveness=refl;}
		Color sample(const Ray3& ray3, const Vec3& position, const Vec3& normal);
};

// global temp

#endif
