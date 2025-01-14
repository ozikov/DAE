#include "pch.h"
#include "Sprite.h"
#include "Texture.h"
#include <iostream>

Sprite::Sprite( const std::string& path, int cols, int rows, float frameSec )
	: m_TexturePath{ path }
	, m_Cols{ cols }
	, m_Rows{ rows }
	, m_FrameSec{ frameSec }
	, m_AccuSec{}
	, m_ActFrame{}
{
	m_pTexture = new Texture( m_TexturePath );
}

Sprite::Sprite(const Sprite& other)
	:Sprite(other.m_TexturePath, other.m_Cols, other.m_Rows, other.m_FrameSec)
{
	std::cout << "copy constructor\n";
}

Sprite::Sprite(Sprite&& other) noexcept
{
	std::cout << "move constructor\n";

	m_TexturePath = other.m_TexturePath;
	m_Cols = other.m_Cols;
	m_Rows = other.m_Rows;
	m_FrameSec = other.m_FrameSec;
	m_AccuSec = other.m_AccuSec;
	m_ActFrame = other.m_ActFrame;
	m_pTexture = other.m_pTexture;

	other.m_TexturePath = "";
	other.m_Cols = 0;
	other.m_Rows = 0;
	other.m_FrameSec = 0.f;
	other.m_AccuSec = 0.f;
	other.m_ActFrame = 0;
	other.m_pTexture = nullptr;
}

Sprite::~Sprite( )
{
	delete m_pTexture;
}

Sprite& Sprite::operator=(const Sprite& rhs)
{
	std::cout << "copy assignment\n";

	delete m_pTexture;

	m_TexturePath = rhs.m_TexturePath;
	m_Cols = rhs.m_Cols;
	m_Rows = rhs.m_Rows;
	m_FrameSec = rhs.m_FrameSec;
	m_AccuSec = rhs.m_AccuSec;
	m_ActFrame = rhs.m_ActFrame;

	return *this;
}

Sprite& Sprite::operator=(Sprite&& rhs) noexcept
{
	std::cout << "move assignment\n";

	delete m_pTexture;

	m_TexturePath = rhs.m_TexturePath;
	m_Cols = rhs.m_Cols;
	m_Rows = rhs.m_Rows;
	m_FrameSec = rhs.m_FrameSec;
	m_AccuSec = rhs.m_AccuSec;
	m_ActFrame = rhs.m_ActFrame;
	m_pTexture = rhs.m_pTexture;

	rhs.m_TexturePath = "";
	rhs.m_Cols = 0;
	rhs.m_Rows = 0;
	rhs.m_FrameSec = 0.f;
	rhs.m_AccuSec = 0.f;
	rhs.m_ActFrame = 0;
	rhs.m_pTexture = nullptr;

	return *this;
}

void Sprite::Update( float elapsedSec )
{
	m_AccuSec += elapsedSec;

	if ( m_AccuSec > m_FrameSec )
	{
		// Go to next frame
		++m_ActFrame;
		if ( m_ActFrame >= m_Cols * m_Rows )
		{
			m_ActFrame = 0;
		}

		// Only keep the remaining time
		m_AccuSec -= m_FrameSec;
	}
}

void Sprite::Draw( const Point2f& pos, float scale ) const
{
	// frame dimensions
	const float frameWidth{  m_pTexture->GetWidth() / m_Cols };
	const float frameHeight{  m_pTexture->GetHeight() / m_Rows };
	int row = m_ActFrame / m_Cols;
	int col = m_ActFrame % m_Cols;

	Rectf srcRect;
	srcRect.height = frameHeight;
	srcRect.width = frameWidth;
	srcRect.left = m_ActFrame % m_Cols * srcRect.width;
	srcRect.bottom = m_ActFrame / m_Cols * srcRect.height + srcRect.height;
	Rectf destRect{ pos.x, pos.y,srcRect.width * scale,srcRect.height * scale };
	m_pTexture->Draw( destRect, srcRect );
}

float Sprite::GetFrameWidth( ) const
{
	return m_pTexture->GetWidth( ) / m_Cols;
}

float Sprite::GetFrameHeight( ) const
{
	return m_pTexture->GetHeight( ) / m_Rows;
}

