objects = main.o vec3.o ray3.o geoobj.o percamera.o material.o color.o
main:$(objects)
	g++ $(objects) -o main -lglut -lGLU -lGL
vec3.o:vec3.cpp vec3.h
	g++ -g -c vec3.cpp
main.o:main.cpp vec3.h
	g++ -g -c main.cpp
ray3.o:ray3.cpp ray3.h vec3.h
	g++ -g -c ray3.cpp
geoobj.o:geoobj.cpp geoobj.h vec3.h ray3.h geoobj.h
	g++ -g -c geoobj.cpp
percamera.o:percamera.cpp vec3.h ray3.h percamera.h
	g++ -g -c percamera.cpp
material.o:material.h vec3.h ray3.h color.h material.cpp light.h
	g++ -g -c material.cpp
color.o:color.h
	g++ -g -c color.cpp

cl:
	rm main $(objects) 
tag:
	ctags -R --fields=+lS
