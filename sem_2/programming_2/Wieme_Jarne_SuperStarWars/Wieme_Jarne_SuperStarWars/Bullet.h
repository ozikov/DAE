#pragma once
#include "Vector2f.h"

class Texture;
class Level;
class Sprite;
class TextureManager;

class Bullet final
{
public:
	enum class Type
	{
		playerNormal,
		playerHeavy,
		Enemy,
		boss
	};

	explicit Bullet(const Point2f& pos, const Vector2f& velocity, TextureManager& pTextureManager, float scale = 1, Type bulletType = Type::playerNormal);
	
	~Bullet( );
	Bullet(const Bullet& bullet) = delete;
	Bullet& operator=(const Bullet& rhs) = delete;
	Bullet(Bullet&& bullet) = delete;
	Bullet& operator=(Bullet&& rhs) = delete;
	
	void Update(float elapsedSec);
	void Draw( ) const;
	bool IsOutOfBoundaries( ) const;
	bool HitGround(const Level& level) const;
	Rectf GetShape( ) const;
	Type GetType( ) const;
	Vector2f GetVelocity( )const;

private:
	Rectf m_Shape;
	Vector2f m_Velocity;
	float m_Scale;
	const Point2f m_StartPos;
	const Texture* m_pTexture;
	Type m_Type;
	Vector2f m_Acceleration;
	Sprite* m_pSprite;
	Rectf m_Boundaries;
};