// -- Smiley.cpp file --
// Decide yourself about the necessary include directives
// #include .....
// ....
#include "pch.h"
#include "Smiley.h"
#include "Texture.h"
#include<math.h>
#include <iostream>

// Static Texture data
Texture* Smiley::m_pSmileyTexture{ nullptr };
int Smiley::m_InstanceCounter{ 0 };

// Constructor
// Initializes the object, among others:
//	- Initializes the data members, the velocity gets a random value within the inclusive range[60, 180] and [-180, -60]
//	- Creates a texture object to load the image, only if it hasn�t been created before( !)
//  - Adapts the instance counter
Smiley::Smiley( const Point2f& position )
	:m_Position{position}
	,m_Velocity{float(rand() % 121 + 60), float(rand() % 121 - 180)}
	,m_IsHighest{}
	,m_IsSleeping{}
	,m_IsInSafeArea{}
{
	++m_InstanceCounter;

	if (m_pSmileyTexture == nullptr)
	{
		m_pSmileyTexture = new Texture("Resources/Smileys.png");
	}

	m_SmileyCircle.radius = m_pSmileyTexture->GetHeight() / 2.f;
	m_SmileyCircle.center = Point2f{ m_Position.x + m_SmileyCircle.radius, m_Position.y + m_SmileyCircle.radius };
}

// Destructor
// Deletes the Texture object when this is the last Smiley that is being destroyed.
Smiley::~Smiley( )
{
	--m_InstanceCounter;

	if (m_InstanceCounter == 0)
	{
		delete m_pSmileyTexture;
	}
}

// Draw
// Draws a part of the image on the window, which part depends on the state of the smiley:
// - If the smiley is sleeping then the sleeping smiley is drawn.
// - If the smiley is at the highest position, then the happy smiley is drawn.
// - If the smiley is not in the safe area, the scary smiley is drawn.
// - If none of the above conditions is met, the neutral smiley should be drawn.
void Smiley::Draw( ) const
{
	Rectf srcRect{};
	srcRect.width = m_pSmileyTexture->GetWidth() / 4.f;
	srcRect.height = m_pSmileyTexture->GetHeight();

	if (m_IsSleeping == true) srcRect.left = 3 * srcRect.width;

	else if (m_IsHighest == true) srcRect.left = 0.f;

	else if (m_IsInSafeArea == false) srcRect.left = 2 * srcRect.width;

	else srcRect.left = srcRect.width;

	glPushMatrix();
		glTranslatef(m_Position.x, m_Position.y, 0);
		m_pSmileyTexture->Draw(Point2f{ 0, 0 }, srcRect);
	glPopMatrix();
}

// Update
// - When the smiley is not sleeping, the new position - using the velocity and elapsed seconds - is calculated.
// - The velocity changes sign when at this new position the smiley is outside the bounding rectangle (boundingRect)
// - Checks whether at this new position, it is located in the safe area and updates m_IsInSafeArea accordingly.
void Smiley::Update( float elapsedSec, const Rectf& boundingRect, const Rectf& safeRect )
{
	if (m_IsSleeping == false)
	{
		m_Position.x += elapsedSec * m_Velocity.x;
		m_Position.y += elapsedSec * m_Velocity.y;

		m_SmileyCircle.radius = m_pSmileyTexture->GetHeight() / 2.f;
		m_SmileyCircle.center = Point2f{ m_Position.x + m_SmileyCircle.radius, m_Position.y + m_SmileyCircle.radius };

		m_IsInSafeArea = IsInSafeArea( safeRect );
	}
	CheckCollision(boundingRect);
}

void Smiley::CheckCollision(const Rectf& boundingRect)
{
	if (m_SmileyCircle.center.x - m_SmileyCircle.radius <= boundingRect.left && std::signbit(m_Velocity.x) == 1)
	{
		m_Velocity.x *= -1;
	}

	if (m_SmileyCircle.center.x + m_SmileyCircle.radius >= boundingRect.left + boundingRect.width && std::signbit(m_Velocity.x) == 0)
	{
		m_Velocity.x *= -1;
	}

	if (m_SmileyCircle.center.y - m_SmileyCircle.radius <= boundingRect.bottom && std::signbit(m_Velocity.y) == 1)
	{
		m_Velocity.y *= -1;
	}

	if (m_SmileyCircle.center.y + m_SmileyCircle.radius >= boundingRect.bottom + boundingRect.height && std::signbit(m_Velocity.y) == 0)
	{
		m_Velocity.y *= -1;
	}
}

// HitTest
// If the value of the parameter pos is within the boundaries of the smiley�s circle,
// then the sleeping state of the smiley changes.
void Smiley::HitTest( const Point2f& pos )
{
	if (utils::IsPointInCircle(pos, m_SmileyCircle)) m_IsSleeping = !m_IsSleeping;
}

// IsSleeping
// Getter of the m_IsSleeping data member
bool Smiley::IsSleeping( ) const
{
	return m_IsSleeping; 
}

// GetPosition
// Getter of the m_Position data member
Point2f Smiley::GetPosition( ) const
{
	return m_SmileyCircle.center;
}

// SetHighest
// Setter of the m_IsHighest data member
void Smiley::SetHighest( bool isHighest )
{
	m_IsHighest = isHighest;
}

// IncreaseSpeed
// Changes the speed 5% up
void Smiley::IncreaseSpeed( )
{
	if (std::signbit(m_Velocity.x) == 1) m_Velocity.x += (m_Velocity.x / 100.f * 5);
	else m_Velocity.x += m_Velocity.x / 100.f * 5;
	
	if (std::signbit(m_Velocity.y) == 1) m_Velocity.y += (m_Velocity.y / 100.f * 5);
	else m_Velocity.y += m_Velocity.y / 100.f * 5;
}

// DecreaseSpeed
// Changes the speed 5% down
void Smiley::DecreaseSpeed( )
{
	if (std::signbit(m_Velocity.x) == 1) m_Velocity.x -= (m_Velocity.x / 100.f * 5);
	else m_Velocity.x -= m_Velocity.x / 100.f * 5;

	if (std::signbit(m_Velocity.y) == 1) m_Velocity.y -= (m_Velocity.y / 100.f * 5);
	else m_Velocity.y -= m_Velocity.y / 100.f * 5;
}

// IsInSafeArea
// Returns true when the smiley is completely inside the safe area as indicated by safeRect
bool Smiley::IsInSafeArea( const Rectf& safeRect ) const
{
	if ( utils::IsPointInRect(Point2f{ m_SmileyCircle.center.x - m_SmileyCircle.radius, m_SmileyCircle.center.y }, safeRect)
		 && utils::IsPointInRect(Point2f{ m_SmileyCircle.center.x + m_SmileyCircle.radius, m_SmileyCircle.center.y }, safeRect)
		 && utils::IsPointInRect(Point2f{ m_SmileyCircle.center.x, m_SmileyCircle.center.y - m_SmileyCircle.radius}, safeRect)
		 && utils::IsPointInRect(Point2f{ m_SmileyCircle.center.x, m_SmileyCircle.center.y + m_SmileyCircle.radius }, safeRect) ) return true;

	return false;
}