#ifndef COLOR_H
#define COLOR_H

class Color
{
	private:
		float r,g,b;
	public:
		Color(float rr, float gr, float br):r(rr),g(gr),b(br){}
		Color():r(0),g(0),b(0){}
		//Color(const Color& rhs){r=rhs.getR();g=rhs.getG();b=rhs.getB();}
		Color add(Color c){return Color( r+c.r, g+c.g, b+c.b);}
		Color multiply(float s){return Color(r*s,g*s,b*s);}
		Color modulate(Color c){return Color(r*c.r, g*c.g, b*c.b);}
		const static Color black, white, red, green, blue;

		float getR()const{return r;}
		float getG()const{return g;}
		float getB()const{return b;}

		void setR(float rr){r=rr;}
		void setG(float gr){g=gr;}
		void setB(float br){b=br;}
};


#endif
