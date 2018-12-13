#include "Color.h"

#include <assert.h>


const Big::Color Big::Color::White(1.0f, 1.0f, 1.0f, 1.0f);
const Big::Color Big::Color::Black(0.0f, 0.0f, 0.0f, 1.0f);
const Big::Color Big::Color::Transparent(0.0f, 0.0f, 0.0f, 0.0f);
const Big::Color Big::Color::Red(1.0f, 0.0f, 0.0f, 1.0f);
const Big::Color Big::Color::Green(0.0f, 1.0f, 0.0f, 1.0f);
const Big::Color Big::Color::Blue(0.0f, 0.0f, 1.0f, 1.0f);
const Big::Color Big::Color::Yellow(1.0f, 1.0f, 0.0f, 0.0f);
const Big::Color Big::Color::Purple(1.0f, 0.0f, 0.0f, 1.0f);


Big::Color::Color()
{

	color[0] = 0.0f;
	color[1] = 0.0f;
	color[2] = 0.0f;
	color[3] = 1.0f;

}


Big::Color::Color(const Color& colorCopy)
{
	color[0] = colorCopy.color[0];
	color[1] = colorCopy.color[1];
	color[2] = colorCopy.color[2];
	color[3] = colorCopy.color[3];
}

Big::Color::Color(float red, float green, float blue, float alpha /*= 1.0f*/)
{
	color[0] = red;
	color[1] = green;
	color[2] = blue;
	color[3] = alpha;



}

Big::Color::~Color()
{
}


float& Big::Color::operator [](int index)
{
	assert(index >= 0 && index < 4);
	return color[index];
}