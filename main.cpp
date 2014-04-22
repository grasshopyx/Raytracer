#include<GL/glut.h>
#include<iostream>
#include<math.h>
#include"vec3.h"
#include"geoobj.h"
#include"percamera.h"
#include"color.h"
#include"material.h"
#include"light.h"


#define X_RES 768
#define Y_RES 768
GLubyte fbuffer[X_RES][Y_RES][3];

class A{
	public:
	int a,b,c;
};


using namespace std;

void Image()
{
	int c;
	for(int i=0;i<Y_RES;i++)
	{
		for(int j=0;j<X_RES;j++)
		{
			fbuffer[i][j][0]=(float)j/X_RES*255;
			fbuffer[i][j][1]=(float)i/Y_RES*255;
			fbuffer[i][j][2]=255;


			// Chess
			c=(((i&0x10)==0)^((j&0x10)==0))*255;
			fbuffer[i][j][0]=(GLubyte)c;
			fbuffer[i][j][1]=(GLubyte)c;
			fbuffer[i][j][2]=(GLubyte)c;
		}
	}
}
int Min(int a, int b)
{
	return a>b?b:a;
}

void renderDepth(Sphere scene, PerspectiveCamera camera, int maxDepth)
{
	for(int y=0;y<Y_RES;y++)
	{
		float sy =  (float)y/Y_RES;
		for(int x=0;x<X_RES;x++)
		{
			float sx = (float)x/X_RES;
			Ray3 ray = camera.generateRay(sx,sy);
			IntersectResult result = scene.intersect(ray);
			if(result.getGeometry())
			{
				int depth = 255 - Min((result.getDistance()/maxDepth)*255,255);
				
				//cout<< "x: " << x << " y: " << y << " depth: "<<depth<<" dis: "<<result.getDistance()<<endl;

				fbuffer[y][x][0]=depth;
				fbuffer[y][x][1]=depth;
				fbuffer[y][x][2]=depth;
			}
		}
	}
}

void renderNormal(Sphere scene, PerspectiveCamera camera)
{
	for(int y=0;y<Y_RES;y++)
	{
		float sy =  (float)y/Y_RES;
		for(int x=0;x<X_RES;x++)
		{
			float sx = (float)x/X_RES;
			Ray3 ray = camera.generateRay(sx,sy);
			IntersectResult result = scene.intersect(ray);
			if(result.getGeometry())
			{

				fbuffer[y][x][0]=(result.getNormal().getx()+1)*128;
				fbuffer[y][x][1]=(result.getNormal().gety()+1)*128;
				fbuffer[y][x][2]=(result.getNormal().getz()+1)*128;
			}
		}
	}
}

void rayTrace( Object& scene, PerspectiveCamera camera)
{
	for(int y=0;y<Y_RES;y++)
	{
		float sy =  (float)y/Y_RES;
		for(int x=0;x<X_RES;x++)
		{
			float sx = (float)x/X_RES;
			Ray3 ray = camera.generateRay(sx,sy);
			IntersectResult result = scene.intersect(ray);
			if(result.getGeometry())
			{
				//Color color = scene.material->sample(ray, result.getPosition(), result.getNormal());
				Color color = result.getGeometry()->material->sample(ray,result.getPosition(),result.getNormal());	
					//CheckMaterial(0.1,1).sample(ray, result.getPosition(), result.getNormal());
				fbuffer[y][x][0]=color.getR()*255;
				fbuffer[y][x][1]=color.getG()*255;
				fbuffer[y][x][2]=color.getB()*255;
			}
		}
	}

}
void rayTrace2( Sphere scene, PerspectiveCamera camera)
{
	for(int y=0;y<Y_RES;y++)
	{
		float sy =  (float)y/Y_RES;
		for(int x=0;x<X_RES;x++)
		{
			float sx = (float)x/X_RES;
			Ray3 ray = camera.generateRay(sx,sy);
			IntersectResult result = scene.intersect(ray);
			if(result.getGeometry())
			{
				cout<<"x:"<<y<<" y:"<<x<<endl;
				Color color = PhongMaterial(Color::red,Color::white,16,1).sample(ray, result.getPosition(), result.getNormal());
				fbuffer[y][x][0]=color.getR()*255;
				fbuffer[y][x][1]=color.getG()*255;
				fbuffer[y][x][2]=color.getB()*255;
			}
		}
	}

}
void rayTrace3( Sphere scene, PerspectiveCamera camera)
{
	for(int y=0;y<Y_RES;y++)
	{
		float sy =  (float)y/Y_RES;
		for(int x=0;x<X_RES;x++)
		{
			float sx = (float)x/X_RES;
			Ray3 ray = camera.generateRay(sx,sy);//
//

			IntersectResult result = scene.intersect(ray);
			if(result.getGeometry())
			{
				cout<<"x:"<<y<<" y:"<<x<<endl;
				Color color = PhongMaterial(Color::blue,Color::white,16,1).sample(ray, result.getPosition(), result.getNormal());
				fbuffer[y][x][0]=color.getR()*255;
				fbuffer[y][x][1]=color.getG()*255;
				fbuffer[y][x][2]=color.getB()*255;
			}
		}
	}

}

Color rayTraceRecursive(Object &scene, Ray3& ray, int maxReflect, DirectionalLight light)
{
	IntersectResult result = scene.intersect(ray);

	//cout<<result.getGeometry()->material->getReflectiveness()<<endl;
	if(result.getGeometry())
	{
		Color color = Color::black;
		Vec3 lightSample = light.sample(scene, result.getPosition());
		//cout<<lightSample.getx()<< " " << lightSample.gety() << " "<<lightSample.getz()<<endl;
		float reflectiveness = result.getGeometry()->material->getReflectiveness(); 	// just the float to int. it is rediculous
		color = result.getGeometry()->material->sample(ray,result.getPosition(),result.getNormal());
		color = color.multiply(1-reflectiveness);

		//	cout << reflectiveness <<endl;
		if(reflectiveness>0 && maxReflect > 0)
		{
			//			cout << reflectiveness <<endl;
			Vec3 r = result.getNormal().multiply(-2*result.getNormal().dot(ray.getDirection())).add(ray.getDirection());
			ray = Ray3(result.getPosition(),r);
			Color reflectedColor = rayTraceRecursive(scene, ray, maxReflect-1,  light);
			color = color.add(reflectedColor.multiply(reflectiveness));
			if(fabs(lightSample.getx())> 1e-4 || fabs(lightSample.gety())> 1e-4 || fabs(lightSample.getz()>1e-4))
			{
			}else{
				color = color.modulate(Color(0.3,0.3,0.3));
			}
		}
		//cout<<"abc"<<endl;
		return color;
	}else{
		return Color::black;
	}
}
void rayTraceReflection(Object& scene, PerspectiveCamera& camera, int maxReflect, DirectionalLight light)
{
	for(int y=0;y<Y_RES;y++)
	{
		float sy =  (float)y/Y_RES;
		for(int x=0;x<X_RES;x++)
		{
			float sx = (float)x/X_RES;
			Ray3 ray = camera.generateRay(sx,sy);
			Color color = rayTraceRecursive(scene, ray, maxReflect, light);
			fbuffer[y][x][0]=color.getR()*255;
			fbuffer[y][x][1]=color.getG()*255;
			fbuffer[y][x][2]=color.getB()*255;
		}
	}
}

void renderLight(Object& scene, PerspectiveCamera& camera, DirectionalLight& light)
{

}

void init()
{
	glClearColor(0.0,0.0,0.0,0.0);
	glShadeModel(GL_FLAT);
	//Image();
	//renderDepth(Sphere(Vec3(0,10,-10),10),PerspectiveCamera(Vec3(0,10,10),Vec3(0,0,-1),Vec3(0,1,0),90),15);
	//renderNormal(Sphere(Vec3(0,10,-10),10),PerspectiveCamera(Vec3(0,10,10),Vec3(0,0,-1),Vec3(0,1,0),90));
	//
	//Material *material = new CheckMaterial(0.1,1);


	Plane plane(Vec3(0,1,0),0,new CheckMaterial(0.1,0.5));
	//	rayTrace(plane, PerspectiveCamera(Vec3(0,5,15),Vec3(0,0,-1),Vec3(0,1,0),90));
	//rayTrace(Plane(Vec3(0,1,0),0), PerspectiveCamera(Vec3(0,5,15),Vec3(0,0,-1),Vec3(0,1,0),90));
	Sphere sphere1(Vec3(-2,5,-5),5,new PhongMaterial(Color::red,Color::white,16,0.25));
	//	rayTrace(sphere1,PerspectiveCamera(Vec3(0,5,15),Vec3(0,0,-1),Vec3(0,1,0),90));
	Sphere sphere2(Vec3(10,10,-10),10,new PhongMaterial(Color::blue, Color::white,16,0.25));
	//	rayTrace(sphere2,PerspectiveCamera(Vec3(0,5,15),Vec3(0,0,-1),Vec3(0,1,0),90)); 
	Sphere sphere3(Vec3(2.5,2,3),2, new PhongMaterial(Color::green, Color::white,16,0.25));

	Plane plane2(Vec3(0,0,1),-50, new Wall(0.8));
	Plane plane3(Vec3(1,0,0),-30, new Wall(0.8));

	Sphere ball1(Vec3(-4,0.5,0),0.5, new PhongMaterial(Color(255/255,(float)89/255,0),Color::white,16,0.25));
	Sphere ball2(Vec3(-2,0.5,0),0.5, new PhongMaterial(Color(255/255,(float)89/255,0),Color::white,16,0.25));
	Sphere ball3(Vec3(-0,0.5,0),0.5, new PhongMaterial(Color(255/255,(float)89/255,0),Color::white,16,0.25));
	Sphere ball4(Vec3(2,0.5,0),0.5, new PhongMaterial(Color(255/255,(float)89/255,0),Color::white,16,0.25));
	Sphere ball5(Vec3(4,0.5,0),0.5, new PhongMaterial(Color(255/255,(float)89/255,0),Color::white,16,0.25));
	Sphere ball6(Vec3(6,0.5,0),0.5, new PhongMaterial(Color(255/255,(float)89/255,0),Color::white,16,0.25));
	Sphere ball7(Vec3(8,0.5,0),0.5, new PhongMaterial(Color(255/255,(float)89/255,0),Color::white,16,0.25));
	Union obj;
	obj.objects.push_back(&plane);
	obj.objects.push_back(&sphere1);
	obj.objects.push_back(&sphere2);
	obj.objects.push_back(&sphere3);
	obj.objects.push_back(&plane2);
	obj.objects.push_back(&plane3);
	
	// balls
	
//	obj.objects.push_back(&ball1);
//	obj.objects.push_back(&ball2);
//	obj.objects.push_back(&ball3);
//	obj.objects.push_back(&ball4);
//	obj.objects.push_back(&ball5);
//	obj.objects.push_back(&ball6);
//	obj.objects.push_back(&ball7);

	//rayTrace(obj, PerspectiveCamera(Vec3(0,5,15),Vec3(0,0,-1),Vec3(0,1,0),90));
	//
	PerspectiveCamera camera = PerspectiveCamera(Vec3(0,5,15),Vec3(0.2,0,-1),Vec3(0,1,0),90);
	DirectionalLight light(Vec3(-1,-1,-1));
	rayTraceReflection(obj,camera,3,light);
	//
	//IntersectResult result;
	//cout << "Result"<<endl;
	//cout << "x:" << result.getPosition().getx() << endl;
	//cout << "y:" << result.getPosition().gety() << endl;
	//cout << "z:" << result.getPosition().getz() << endl;
	//
	//glPixelStorei(GL_UNPACK_ALIGNMENT,1);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//glColor3f(1.0,1.0,1.0);
	//glRasterPos2i(0,0);


	//	const Vec3 zero2 = Vec3(0,0,0);
	// it will be executed twice or more	
	//cout << "x:" << Vec3::zero.getx() << endl << "y:"<< Vec3::zero.gety()<<endl<< "z:"<< Vec3::zero.getz()<<endl;




	glDrawPixels(X_RES,Y_RES,GL_RGB,GL_UNSIGNED_BYTE,fbuffer);

	glFlush();
}
//void reshape()
//{
//	
//}
int main(int argc, char**argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(X_RES, Y_RES);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Raytracer");

	init();
	glutDisplayFunc(display);
	//	glutReshapeFunc(reshape);

	glutMainLoop();

	return 0;
}
