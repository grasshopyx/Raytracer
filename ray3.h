#ifndef RAY3_H
#define RAY3_H

#include"vec3.h"
class Ray3{
	private:
		Vec3 origin;
		Vec3 direction;	
	public:
		Ray3(const Vec3& origin, const Vec3& direction)
		{
			this->origin=origin;
			this->direction=direction;
		}
		Vec3 getPoint(float)const;
		Vec3 getOrigin()const;
		Vec3 getDirection()const;
};
#endif
