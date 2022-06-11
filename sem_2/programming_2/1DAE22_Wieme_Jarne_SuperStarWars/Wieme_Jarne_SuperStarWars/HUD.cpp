#include "pch.h"
#include "HUD.h"
#include "TextureManager.h"
#include "Texture.h"
#include "utils.h"

HUD::HUD(const Point2f& topLeft, int totalAvatarHearts, int totalAvatarHealth, TextureManager& textureManager)
	: m_TotalAvatarHearts{ totalAvatarHearts }
	, m_AmountOfHearts{ totalAvatarHearts }
	, m_TotalAvatarHealth{ float(totalAvatarHealth) }
	, m_AvatarHealth{ totalAvatarHealth }
	, m_pHealthBar{ textureManager.GetTexture("Resources/HUD/HealthBar.png") }
	, m_pNumberZero{ textureManager.GetTexture("Resources/HUD/Numbers/0.png") }
	, m_pNumberOne{ textureManager.GetTexture("Resources/HUD/Numbers/1.png") }
	, m_pNumberTwo{ textureManager.GetTexture("Resources/HUD/Numbers/2.png") }
	, m_pNumberThree{ textureManager.GetTexture("Resources/HUD/Numbers/3.png") }
	, m_BottomLeft{topLeft.x, topLeft.y - m_pHealthBar->GetHeight() }
{
}

HUD::~HUD( )
{
}

void HUD::Update(int avatarHealth, int amountOfHearts)
{
	m_AvatarHealth = avatarHealth;
	m_AmountOfHearts = amountOfHearts;
}

void HUD::Draw( ) const
{
	glPushMatrix( );
		glTranslatef(m_BottomLeft.x, m_BottomLeft.y, 0.f);
		m_pHealthBar->Draw( );

		glTranslatef(70.f, 18.f, 0.f);

		switch (m_AmountOfHearts)
		{
		case 0:
			m_pNumberZero->Draw( );
			break;

		case 1:
			m_pNumberOne->Draw( );
			break;

		case 2:
			m_pNumberTwo->Draw( );
			break;

		case 3:
			m_pNumberThree->Draw( );
			break;
		}
		
		glTranslatef(-70.f, -18.f, 0.f);

		Rectf healthRect{};
		healthRect.width = m_AvatarHealth / m_TotalAvatarHealth * 124.f;
		healthRect.height = 2.f;

		utils::SetColor(Color4f{ 80 / 255.f, 148 / 255.f, 149 / 255.f, 1.f });

		glTranslatef(33.f, 4.f, 0.f);
		utils::FillRect(healthRect);

		glTranslatef(0.f, 6.f, 0.f);
		utils::FillRect(healthRect);

		healthRect.width = m_AvatarHealth / m_TotalAvatarHealth * 126.f;
		healthRect.height = 4.f;

		utils::SetColor(Color4f{ 173 / 255.f, 222 / 255.f, 1.f, 1.f });
		
		glTranslatef(0.f, -4.f, 0.f);
		utils::FillRect(healthRect);

	glPopMatrix( );
}

void HUD::LostHeart( )
{
	--m_AmountOfHearts;
}

void HUD::LostHealth( )
{
	--m_AvatarHealth;
}