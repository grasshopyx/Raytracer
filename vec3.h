#ifndef VEC3_H
#define VEC3_H
class Vec3{
	public:
		Vec3(float xr,float yr,float zr):x(xr),y(yr),z(zr){}
		Vec3():x(0),y(0),z(0){}
		Vec3(const Vec3& vec):x(vec.x),y(vec.y),z(vec.z){}
		Vec3& copy(); 	// no use. special for JavaScript
		float length()const;
		float sqLength()const;
		Vec3 normalize()const;
		Vec3 negate()const;
		Vec3 add(const Vec3&)const;
		Vec3 substract(const Vec3&)const;
		Vec3 multiply(const float)const;
		Vec3 divide(const float)const;
		float dot(const Vec3&)const;
		Vec3 cross(const Vec3&)const;
		float getx()const;
		float gety()const;
		float getz()const;

	//	bool operator==(const Vec3& lhs, const Vec3& rhs)
	//	{
	//		return lhs.x==rhs.x && lhs.y==rhs.y && lhs.z==rhs.z
	//	}
	//	bool operator!=(const Vec3& lhs, const Vec3& rhs)
	//	{
	//		return !(lhs==rhs);
	//	}

		const static Vec3 zero; 	// as a declaration, not a definition
		//static const Vec3 zero2 = Vec3(0,0,0);
	private:
		float x,y,z;
		//static const Vec3 zero = Vec3(0,0,0); 	I can't make this const
};
#endif
