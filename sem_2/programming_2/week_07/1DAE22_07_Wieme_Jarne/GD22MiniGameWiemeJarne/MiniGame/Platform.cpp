#include "pch.h"
#include "Platform.h"
#include "Texture.h"
#include "utils.h"
#include <iostream>

Platform::Platform(const Point2f& bottomLeftPoint)
	:m_Shape{bottomLeftPoint.x, bottomLeftPoint.y, 0, 0}
	,m_pTexture{ new Texture{"Resources/Images/platform.png"} }
{
	m_Shape.width = m_pTexture->GetWidth();
	m_Shape.height = m_pTexture->GetHeight();
}

Platform::~Platform()
{
	delete m_pTexture;
}

void Platform::Draw() const
{
	glPushMatrix();
		glTranslatef(m_Shape.left, m_Shape.bottom, 0);
		m_pTexture->Draw();
	glPopMatrix();
}

void Platform::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const
{
	if (actorVelocity.y <= 0)
	{
		std::vector<Point2f> vertices{};
		vertices.push_back(Point2f{m_Shape.left, m_Shape.bottom + m_Shape.height});
		vertices.push_back(Point2f{ m_Shape.left + m_Shape.width, m_Shape.bottom + m_Shape.height });

		Point2f rayStartPoint{ actorShape.left + actorShape.width / 2.f,
							   actorShape.bottom + actorShape.height    };
		Point2f rayEndPoint{ actorShape.left + actorShape.width / 2.f,
							 actorShape.bottom						  };

		utils::HitInfo hitInfo{};

		if (utils::Raycast(vertices, rayStartPoint, rayEndPoint, hitInfo))
		{
			actorShape.bottom = hitInfo.intersectPoint.y;
			actorVelocity.y = 0.f;
		}
	}
}

bool Platform::IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const
{
	if ( actorVelocity.y <= 0 )
	{
		std::vector<Point2f> vertices{};
		vertices.push_back(Point2f{ m_Shape.left, m_Shape.bottom + m_Shape.height });
		vertices.push_back(Point2f{ m_Shape.left + m_Shape.width, m_Shape.bottom + m_Shape.height });

		Point2f rayStartPoint{ actorShape.left + actorShape.width / 2.f,
							   actorShape.bottom + actorShape.height };
		Point2f rayEndPoint{ actorShape.left + actorShape.width / 2.f,
							 actorShape.bottom };

		utils::HitInfo hitInfo{};

		if (utils::Raycast(vertices, rayStartPoint, rayEndPoint, hitInfo))
		{
			return true;
		}
	}
	return false;
}