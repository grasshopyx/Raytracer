#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H
#include"vec3.h"
#include"ray3.h"
#include"math.h"
class PerspectiveCamera
{
	public:
		Vec3 eye;
		Vec3 front;
		Vec3 refUp;
		float fov;
		PerspectiveCamera(const Vec3& eye, const Vec3& front, const Vec3& up,float fov){
			this->eye=eye;
			this->front=front;
			this->refUp=up;
			this->fov=fov;

			this->right = this->front.cross(refUp);
			this->up = this->right.cross(this->front);
			fovScale = tan( fov * 0.5 * M_PI / 180) *2;
		}
		Ray3 generateRay(float,float);
	private:
		Vec3 right;
		Vec3 up;
		float fovScale;
		
};
#endif
