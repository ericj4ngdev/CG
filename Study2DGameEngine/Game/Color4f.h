#ifndef COLOR_H_
#define COLOR_H_
class Color4f
{
	float r, g, b, a;
public:
	Color4f() {}
	Color4f(float tr, float tg, float tb, float ta) : r(tr), g(tg), b(tb), a(ta) {}
};

#endif