#include"percamera.h"
Ray3 PerspectiveCamera::generateRay(float x, float y)
{
	Vec3 r = right.multiply((x-0.5)*fovScale);
	Vec3 u = up.multiply((y-0.5)*fovScale);
	return Ray3(eye, front.add(r).add(u).normalize());
}
