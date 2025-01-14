#pragma once
#include "Vector2f.h"
#include "DaeEllipse.h"

class DaeCircle final : public DaeEllipse
{
public:
	DaeCircle( const Point2f& center, float diameter, const Color4f& color, bool isFilled );

private: 
	float m_Diameter;
};