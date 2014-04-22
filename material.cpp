#include<math.h>
#include"material.h"
#include<iostream>
#include"light.h"
using namespace std;


Color CheckMaterial::sample(const Ray3& ray, const Vec3& position, const Vec3& normal)
{
	return fabs((int)(floor(position.getx()*0.1)+floor(position.getz()*scale))%2)<1 ? Color::black : Color::white;
}
Color PhongMaterial::sample(const Ray3& ray, const Vec3& position, const Vec3& normal)
{
	// i don't know why global will lead to ld error
	//Vec3 lightDir = Vec3(1,1,1).normalize();
	//Color lightColor = Color::white;

//	Vec3 lightDir = Vec3(1,1,1).normalize();
	DirectionalLight lightDir(Vec3(-1,-1,-1));

	Color lightColor = Color::white;

	float NdotL = normal.dot(lightDir.L);
	//cout << "NdotL: " << NdotL << endl;
	Vec3 H = lightDir.L.substract(ray.getDirection()).normalize();
	float NdotH = normal.dot(H);
	//cout << "NdotH: " << NdotH << endl;
	Color diffuseTerm = diffuse.multiply(fmax(NdotL,0));
	Color specularTerm = specular.multiply( pow( fmax(NdotH,0), shininess));
//	cout << "diffTerm: " << diffuseTerm.getR() << " "<<diffuseTerm.getG() << " " << diffuseTerm.getB()  << endl;
//	cout << "specTerm: " << specularTerm.getR() << " " << specularTerm.getG() << " " << specularTerm.getB() << endl;
	
	Color ret = lightColor.modulate(diffuseTerm.add(specularTerm));
	if(ret.getR()>1) 	// it is possible that the color is overflow
	{
		ret.setR(1);

	}
	if(ret.getB()>1)
	{
		ret.setB(1);
	}
	if(ret.getG()>1)
	{
		ret.setG(1);
	}

	Color add = diffuseTerm.add(specularTerm);
	Color modulate = lightColor.modulate((add));

	//cout << "add: " << add.getR() << " " << add.getG() << " " << add.getB() << endl;
	//cout << "modulate: " << modulate.getR() << " " << modulate.getG() << " " << modulate.getB() << endl;

	//cout << "lightColor: " << lightColor.getR() << " " << lightColor.getG() << " " << lightColor.getB() << endl;


	//cout << "ret: " << ret.getR() << " " << ret.getG() << " " << ret.getB() << endl;
	return ret;
}
