#pragma once

namespace PG {

//--------------------------------------------------------
class Colour
{
public:
	//--------------------------------------------------------
	Colour(unsigned char r_, unsigned char g_, unsigned char b_, float a_=1.0)
	: r(r_), g(g_), b(b_), a(a_)
	{}
	
	//--------------------------------------------------------
	Colour()
	: r(0), g(0), b(0), a(1.0)
	{}

	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	float			a;
	
	static Colour white();
	static Colour black();
	static Colour red();
	static Colour green();
	static Colour blue();
};

}
