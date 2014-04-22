#ifndef LIGHT_H
#define LIGHT_H
#include"geoobj.h"
class DirectionalLight 
{
	public:
		Vec3 direction;
		Vec3 L;
		const static bool shadow=true;
		DirectionalLight(Vec3 direction)
		{
			L = direction.normalize().negate();
		}
		Vec3 sample(Object& scene, Vec3& position)
		{
			if(shadow)
			{
				Ray3 shadowRay = Ray3(position,L);
				IntersectResult shadowResult = scene.intersect(shadowRay);
				if(shadowResult.getGeometry())
					return Vec3::zero;
			}	
			return L;
		}
};
#endif
