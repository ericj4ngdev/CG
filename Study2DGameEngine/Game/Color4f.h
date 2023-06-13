#ifndef COLOR_H_
#define COLOR_H_
class Color4f
{
public:
	float r, g, b, a;
	Color4f() { r = 0, g = 0, b = 0, a = 0; }
	Color4f(float tr, float tg, float tb, float ta) : r(tr), g(tg), b(tb), a(ta) {}
};

#endif